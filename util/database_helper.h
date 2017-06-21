/**
 * Copyright 2017 OOP-Cash Team

 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file   database_helper.h
 * @author Harry Chen <harry-chen@outlook.com>
 * @date   2017.05
 * @brief  Header file of class DatabaseHelper
 */

#ifndef DATABASE_HELPER_H
#define DATABASE_HELPER_H

#include <sqlpp11/sqlpp11.h>
#include <sqlpp11/sqlite3/sqlite3.h>

/**
 * @brief Manage the connection of database.
 * @details Singleton mode, only one connection is allowed at the same time
 */
class DatabaseHelper
{
public:
    /**
     * @brief Initialize the connection to database
     *
     * Read the configuration if exists, ask the user for a new location
     * and store it if configuration not found or not valid
     */
    static void initializeDatabase();
    /**
     * @brief Close the database connection
     */
    static void closeDatabase();
    /**
     * @brief Get the database connection object
     * @return the pointer of database connection
     */
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
