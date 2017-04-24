#include <QApplication>
#include <QDebug>
#include <sqlpp11/sqlpp11.h>

#include "util/common.h"
#include "util/database_helper.h"


namespace sql = sqlpp::sqlite3;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    logging::Logger::instance().setLogDir(QCoreApplication::applicationDirPath().toStdString());
    logging::Logger::instance().setLogFilePrefix(APP_NAME.toStdString());
#ifdef _DEBUG
    logging::Logger::instance().setMinLevel(logging::l_trace);
#else
    logging::Logger::instance().setMinLevel(logging::l_info);
#endif


    logging::trace("Application Start===========");
    logging::trace("中文测试");

    DatabaseHelper::initializeDatabase();
    sql::connection *db = DatabaseHelper::getDb();
    try{
    db->execute(R"(CREATE TABLE tab_sample (
          alpha INTEGER PRIMARY KEY,
              beta varchar(255) DEFAULT NULL,
              gamma bool DEFAULT NULL
              ))");
    }
    catch(sqlpp::exception e){
        logging::error(std::string("Error executing SQL statement:\n") + e.what());
        qDebug() << e.what() << endl;
    }

    logging::trace("Application End===========");
    return 0;
}
