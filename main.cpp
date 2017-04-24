#include <QApplication>
#include <QDebug>
#include <sqlpp11/sqlpp11.h>
#include "util/database_helper.h"

namespace sql = sqlpp::sqlite3;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
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
        qDebug() << e.what() << endl;
    }
    return 0;
}
