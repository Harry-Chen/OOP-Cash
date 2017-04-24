#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include "util/database_helper.h"
#include "util/configuration.h"

#pragma execution_character_set("utf-8")

namespace sql = sqlpp::sqlite3;

bool DatabaseHelper::isDatabaseInitialized = false;
sql::connection_config* DatabaseHelper::config = nullptr;
sql::connection* DatabaseHelper::db = nullptr;

void DatabaseHelper::initializeDatabase()
{
    if(!isDatabaseInitialized){
        QString path = Configuration::getDatabasePath();
        if(path == "" || !QFile(path).exists()){
            path = setNewDatabasePath();
        }
        config = new sql::connection_config();
        config->path_to_database = path.toUtf8().constData();
        config->flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;
        config->debug = true;
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
