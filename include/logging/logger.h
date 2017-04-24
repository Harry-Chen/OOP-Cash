#ifndef LOGGER_H
#define LOGGER_H

#include <sstream>

#ifdef QT_CORE_LIB
#include <QString>
#endif

namespace logging {

///Logging levels
enum Level
{
    l_trace = -2,
    l_debug = -1,
    l_info = 0,
    l_error = 1
};

/// Handler for gui log message realtime output
typedef void(*GuiLogMessageHandler)(void* data, const std::string& prefix, const std::string& msg);

/// Logger singletone. Controls life time of internal logging thread
class Logger
{
public:

    static Logger& instance();
    ~Logger();

    ///set callback for custom logging widget etc
    void setMessageHandler(GuiLogMessageHandler handler, void *handlerData);

    ///write stringstream to log. stream will be cleared
    void writeStream(std::stringstream& stream, Level level);

    ///directory where all logs are placed
    void setLogDir(const std::string& logDir);
    std::string getLogDir();

    ///Log file names are made of <prefix>_yyyymmdd.log
    void setLogFilePrefix(const std::string& logFilePrefix);
    std::string getFilePrefix();

    ///Minimum level message filter
    void setMinLevel(const Level minLevel);
    Level getMinLevel() const;

    ///Stop logging threads. After calling this method all file io stops.
    void stop();

    ///auto-clean file interval (deletes only 1 file). Default = 0 <=> OFF
    void setDaysToKeep(int daysToKeep);

private:
    Logger();
    Logger(const Logger&);
    Logger(const Logger&&);
    Logger& operator=(const Logger&);
    Logger& operator=(const Logger&&);

    class LoggerImpl;
    LoggerImpl* d_;
};

/// Helper class for simple syntax logging.
/// Feel free to add overloads for operator << for unsupported types.
template <Level level>
class StreamLoggerHelper {
public:
    StreamLoggerHelper() {}

#ifdef QT_CORE_LIB
    StreamLoggerHelper& operator<< (const QString& str) { stream << str.toStdString(); return *this; }
    StreamLoggerHelper& operator<< (const QByteArray& str) { stream << QString(str).toStdString(); return *this; }
#else
    StreamLoggerHelper& operator<< (const std::string& str) { stream << str; return *this; }
#endif

    ///general logging method
    template<class T>
    StreamLoggerHelper& operator << (const T& msg)      { stream << msg;               return *this; }

    ///template ctor
    template<class T>
    StreamLoggerHelper(const T& str) { *this << str; }

    ///dtor flushes stream contents to logging queue using writeStream() method
    ~StreamLoggerHelper()                               { Logger::instance().writeStream(stream, level); }

private:
    std::stringstream stream;

    //disable copying
    StreamLoggerHelper(const StreamLoggerHelper&);
    StreamLoggerHelper& operator=(const StreamLoggerHelper&);
};

typedef StreamLoggerHelper<l_trace> trace;
typedef StreamLoggerHelper<l_debug> debug;
typedef StreamLoggerHelper<l_info>  info;
typedef StreamLoggerHelper<l_error> error;

} //ns logging



#endif //LOGGER_H
