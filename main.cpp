﻿#include <QApplication>
#include <QDebug>
#include <sqlpp11/sqlpp11.h>

#include "util/common.h"
#include "util/database_helper.h"
#include "database/tables.h"


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

    DatabaseHelper::initializeDatabase();
    sql::connection &db = *(DatabaseHelper::getDb());
    Table::User user;
    ;
    for(const auto &row : db(select(user.username, user.nickname).from(user).unconditionally())){
        logging::trace(std::string(row.username) + ", "  + std::string(row.nickname));
    }
    logging::trace("Application End===========");
    return 0;
}
