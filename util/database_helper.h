#ifndef DATABASE_HELPER_H
#define DATABASE_HELPER_H

#include <sqlpp11/sqlpp11.h>
#include <sqlpp11/sqlite3/sqlite3.h>

class DatabaseHelper
{
public:
    static void initializeDatabase();
    static void closeDatabase();
    static sqlpp::sqlite3::connection* getDb();
private:
    static bool isDatabaseInitialized;
    static sqlpp::sqlite3::connection_config *config;
    static sqlpp::sqlite3::connection *db;
    static void makeNewDatabase();
    static void initializeDatabaseConnection(const QString &path);
    static void buildDatabaseStructure();
};

#endif // DATABASE_HELPER_H
