#include <QApplication>
#include <QDebug>
#include <sqlpp11/sqlpp11.h>
#include <sqlpp11/sqlite3/sqlite3.h>

namespace sql = sqlpp::sqlite3;

int main(int argc, char *argv[])
{
    sql::connection_config config;
    config.path_to_database = "test.sqlite";
    config.flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;
    config.debug = true;
    sql::connection db(config);

    try{
    db.execute(R"(CREATE TABLE tab_sample (
          alpha INTEGER PRIMARY KEY,
              beta varchar(255) DEFAULT NULL,
              gamma bool DEFAULT NULL
              ))");
    db.execute(R"(CREATE TABLE tab_foo (
          omega bigint(20) DEFAULT NULL
              ))");
    }
    catch(sqlpp::exception e){
        qDebug() << e.what() << endl;
    }

    return 0;
}
