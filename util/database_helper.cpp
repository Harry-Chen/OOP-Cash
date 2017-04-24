#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include "util/database_helper.h"
#include "util/configuration.h"
#include "util/common.h"

namespace sql = sqlpp::sqlite3;

bool DatabaseHelper::isDatabaseInitialized = false;
sql::connection_config* DatabaseHelper::config = nullptr;
sql::connection* DatabaseHelper::db = nullptr;

void DatabaseHelper::initializeDatabase()
{
    if(!isDatabaseInitialized){
        logging::trace("Initializing database...");
        QString path = Configuration::getDatabasePath();
        if(path == "" || !QFile(path).exists()){
            path = setNewDatabasePath();
        }
        logging::trace(std::string() + "Database path: " + path.toStdString());
        config = new sql::connection_config();
        config->path_to_database = path.toStdString();
        config->flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;
#ifdef _DEBUG
        config->debug = true;
#endif
        db = new sql::connection(*config);
    }
    isDatabaseInitialized = true;
}

sqlpp::sqlite3::connection *DatabaseHelper::getDb()
{
    if(isDatabaseInitialized) return db;
    else return nullptr;
}

QString DatabaseHelper::setNewDatabasePath()
{
    QString path;
    while(path == ""){
        QMessageBox::information(nullptr, QObject::tr("提醒"), QObject::tr("未设置默认数据库路径或文件不存在"), QMessageBox::Ok);
        path = QFileDialog::getSaveFileName(nullptr, QObject::tr("创建新的数据库"), "", QObject::tr("SQLite 数据库 (*.sqlite *.db)"));
    }
    Configuration::setDatabasePath(path);
    return path;
}
