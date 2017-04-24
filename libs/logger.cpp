#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
#include <ctime>
#include <mutex>
#include <queue>
#include <thread>
#include <condition_variable>

#include "../include/logging/logger.h"

namespace logging {

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
    #include <windows.h>
#else
    #include <sys/time.h>
#endif

int getMilliseconds() {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)

    static DWORD first = GetTickCount();
    return (GetTickCount() - first) % 1000;

#else

    static struct timeval tv;
    gettimeofday(&tv, 0);
    return tv.tv_usec / 1000;

#endif
}

void setLevelPrefix(char* buf, const Level level) {

    switch(level) {
    case l_info:
        *buf = 'I';
        break;
    case l_error:
        *buf = 'E';
        break;
    case l_debug:
        *buf = 'D';
        break;
    case l_trace:
        *buf = 'T';
        break;
    default:
        *buf = '*';
        break;
    }
    buf[1] = ' ';
}

std::string getLogFileName(const std::string& logFilePrefix, time_t fileTime = time(0)) {

    char timeFormatBuffer[80];

    const tm& timeInfo = *localtime( &fileTime );
    strftime(timeFormatBuffer, sizeof(timeFormatBuffer), "%Y%m%d", &timeInfo);

    return logFilePrefix + "_" + timeFormatBuffer + ".log";
}

int getDayOfMonth(time_t unixTime) {
    return localtime( &unixTime )->tm_mday;
}

struct LogMessage {

    time_t time_;
    int milliseconds_;
    const Level level_;
    std::string text_;

    LogMessage(const std::stringstream& stream, const Level level) :
        time_( time(nullptr) ),
        milliseconds_( getMilliseconds() ),
        level_( level ),
        text_( stream.str() )
    {
    }

    std::string getPrefix() const {

        char result[64];

        setLevelPrefix(result, level_);
        const tm timeInfo = *localtime( &time_);
        size_t offset = 2+strftime(result+2, sizeof(result), "%Y.%m.%d %H:%M:%S", &timeInfo);
        std::sprintf(result+offset, ".%03d ", milliseconds_);

        return result;
    }
};

class Logger::LoggerImpl {

public:

    LoggerImpl() {
        minLevel_ = l_trace;
        logFilePrefix_ = "log";
        guiLogMessageHandler_ = nullptr;
        guiLogMessageHandlerData_ = nullptr;
        run_ = false;
        daysToKeep_ = 0;

        setLogDir(".");
    }

    ~LoggerImpl() {
        setMessageHandler(nullptr, nullptr);
        stopFileThread();
    }

    void writeStream(std::stringstream &stream, Level level) {
        if(level >= minLevel_) {
            std::unique_lock<std::mutex> lk(writelock_);
            messageQueue_.emplace( LogMessage(stream, level) );
            if(messageQueue_.size() > 1024)
                cv_.notify_one();
        }
    }
    void setMessageHandler(GuiLogMessageHandler handler, void *handlerData) {
        std::unique_lock<std::mutex> lk(writelock_);
        guiLogMessageHandlerData_ = handlerData;
        guiLogMessageHandler_ = handler;
    }

    std::string getLogFilePrefix() {
        std::unique_lock<std::mutex> lk(writelock_);
        return logFilePrefix_;
    }
    void setLogFilePrefix(const std::string &logFilePrefix) {

        if(logFilePrefix_ == logFilePrefix)
            return;

        stopFileThread();

        logFilePrefix_ = logFilePrefix;

        startFileThread();
    }

    std::string getLogDir() {
        std::unique_lock<std::mutex> lk(writelock_);
        return logDir_;
    }

    void setLogDir(const std::string &logDir) {

        if(logDir_ == logDir)
            return;

        stopFileThread();

        logDir_ = logDir;
        if(!logDir_.empty()) {
            char lastChar = logDir_.at(logDir_.length() - 1);
            if(lastChar != '/' &&  lastChar != '\\')
                logDir_ += '/';
        }
        startFileThread();
    }

    Level getMinLevel() const {
        return minLevel_;
    }

    void setMinLevel(const Level minLevel) {
        minLevel_ = minLevel;
    }

    void startFileThread() {
        run_ = true;
        worker_ = std::thread(&Logger::LoggerImpl::threadProc, this, logDir_ + logFilePrefix_);
    }

    void stopFileThread() {
        run_ = false;
        if(worker_.joinable())
            worker_.join();
    }


    void setDaysToKeep(int daysToKeep)
    {
        daysToKeep_ = daysToKeep;
    }


private:
    std::mutex writelock_;

    Level minLevel_;
    std::string logDir_;
    std::string logFilePrefix_;
    GuiLogMessageHandler guiLogMessageHandler_;
    void *guiLogMessageHandlerData_;
    bool run_;
    std::condition_variable cv_;
    std::thread worker_;
    std::queue<LogMessage> messageQueue_;
    int daysToKeep_;

    void threadProc(const std::string& logFilePrefix) {

        std::ofstream file;

        int dayOfMonth = getDayOfMonth( time(0) );

        while(run_) {

            std::unique_lock<std::mutex> lk(writelock_);
            cv_.wait_for(lk,
                        std::chrono::milliseconds(300),
                        [&]{ return run_ && !messageQueue_.empty(); }
            );

            if(messageQueue_.empty())
                continue;

            std::queue<LogMessage> tmpQueue;
            tmpQueue.swap(messageQueue_);

            lk.unlock();

            if(!writeLogMessageQueueToFile(file, tmpQueue, dayOfMonth, logFilePrefix))
                return;
        }

        //flush the messages left in queue
        std::unique_lock<std::mutex> lk(writelock_);

        writeLogMessageQueueToFile(file, messageQueue_, dayOfMonth, logFilePrefix);
        file.close();
    }


    bool openLogFile(std::ofstream& file, const std::string &logFilePrefix) {

        if(file.is_open())
            file.close();

        //clean 1 old file for 24x7 applications
        if (daysToKeep_>0) {
            time_t removeTime = time(0) - daysToKeep_*24*3600;
            remove(getLogFileName(logFilePrefix, removeTime).c_str());
        }

        std::string filename = getLogFileName(logFilePrefix);

        file.open(filename, std::ios_base::app );

        return file.good();
    }

    void writeToFile(std::ofstream& file, const LogMessage& lm) {

        std::string prefix = lm.getPrefix();

        file << prefix << lm.text_ << std::endl;

        if(guiLogMessageHandler_)
            guiLogMessageHandler_(guiLogMessageHandlerData_, prefix, lm.text_);
    }

    bool writeLogMessageQueueToFile(std::ofstream& file,
                                    std::queue<LogMessage> &lmQueue,
                                    int dayOfMonth,
                                    const std::string &logFilePrefix)
    {
        while(!lmQueue.empty()) {
            LogMessage& lm = lmQueue.front();

            if (!file.is_open() || !file.good() || //open if file is not open
                 (getDayOfMonth(lm.time_) > dayOfMonth)) //open new log file if day have passed
            {
                if (!openLogFile(file, logFilePrefix)) {
                    std::cerr << "Error opening log file"<< std::endl;
                    return false;
                }
            }

            writeToFile(file, lm);
            lmQueue.pop();
        }
        return true;
    }
};

Logger &Logger::instance() {
    static Logger instance;
    return instance;
}

Logger::Logger() :
    d_(new LoggerImpl)
{
}

Logger::~Logger() {
    delete d_;
    d_=nullptr;
}

void Logger::setMessageHandler(GuiLogMessageHandler handler, void *handlerData) {
    d_->setMessageHandler(handler,handlerData);
}

void Logger::writeStream(std::stringstream &stream, Level level) {
    d_->writeStream(stream,level);
}

void Logger::setLogDir(const std::string &logDir) {
    d_->setLogDir(logDir);
}

std::string Logger::getLogDir() {
    return d_->getLogDir();
}

void Logger::setLogFilePrefix(const std::string &logFilePrefix) {
    d_->setLogFilePrefix(logFilePrefix);
}

std::string Logger::getFilePrefix() {
    return d_->getLogFilePrefix();
}

Level Logger::getMinLevel() const {
    return d_->getMinLevel();
}

void Logger::setMinLevel(const Level minLevel) {
    d_->setMinLevel(minLevel);
}

void Logger::stop()
{
    d_->stopFileThread();
}

void Logger::setDaysToKeep(int daysToKeep)
{
    d_->setDaysToKeep(daysToKeep);
}

} //ns logging
