﻿/**
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
 * @file   database_helper.cpp
 * @author Harry Chen <harry-chen@outlook.com>
 * @date   2017.05
 * @brief  Implementation file of class DatabaseHelper
 */

#include <QMessageBox>
#include <QFileDialog>
#include <QFile>

#include "util/database_helper.h"
#include "util/configuration.h"

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
            makeNewDatabase();
        }
        else{
            initializeDatabaseConnection(path);
        }
    }
    isDatabaseInitialized = true;
}

void DatabaseHelper::closeDatabase()
{
    if(isDatabaseInitialized){
        delete db;
        db = nullptr;
        isDatabaseInitialized = false;
    }
}

sqlpp::sqlite3::connection *DatabaseHelper::getDb()
{
    if(isDatabaseInitialized) return db;
    else return nullptr;
}

void DatabaseHelper::makeNewDatabase()
{
    logging::trace("Database not valid, creating a new one.");
    QString path;
    while(path == ""){
        QMessageBox::information(nullptr, QObject::tr("提醒"), QObject::tr("未设置默认数据库路径或文件不存在"), QMessageBox::Ok);
        path = QFileDialog::getSaveFileName(nullptr, QObject::tr("创建新的数据库"), "", QObject::tr("SQLite 数据库 (*.sqlite *.db)"));
    }
    Configuration::setDatabasePath(path);
    initializeDatabaseConnection(path);
    buildDatabaseStructure();
}

void DatabaseHelper::initializeDatabaseConnection(const QString &path)
{
    logging::debug(std::string() + "Database path: " + path.toStdString());
    config = new sql::connection_config();
    config->path_to_database = path.toStdString();
    config->flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;
#ifdef _DEBUG
	config->debug = true;
#endif
    db = new sql::connection(*config);
}

void DatabaseHelper::buildDatabaseStructure()
{
    logging::info("Building new database structure");
    try{
        db->execute(R""(CREATE TABLE `User` (
                `id`	INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,
                `username`	TEXT NOT NULL,
                `nickname`	TEXT,
                `password`	TEXT NOT NULL
            );)"");
        db->execute(R""(CREATE TABLE `Currency` (
                `id`	INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,
                `uid`	INTEGER NOT NULL,
                `name`	TEXT NOT NULL,
                `rate`	INTEGER NOT NULL,
                FOREIGN KEY(`uid`) REFERENCES `User`(`id`)
            );)"");
        db->execute(R""(CREATE TABLE "Account" (
                `id`	INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,
                `name`	TEXT NOT NULL,
                `uid`	INTEGER NOT NULL,
                `cid`	INTEGER NOT NULL,
                FOREIGN KEY(`uid`) REFERENCES User(id),
                FOREIGN KEY(`cid`) REFERENCES Currency(id)
             );)"");
        db->execute(R""(CREATE TABLE "Category" (
                    `id`	INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,
                    `name`	TEXT NOT NULL,
                    `uid`	INTEGER NOT NULL,
                    FOREIGN KEY(`uid`) REFERENCES User(id)
             );)"");
        db->execute(R""(CREATE TABLE `Bill` (
                `id`	INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,
                `afrom`	INTEGER NOT NULL,
                `ato`	INTEGER NOT NULL,
                `creator`	INTEGER NOT NULL,
                `category`	INTEGER NOT NULL,
                `quantity`	INTEGER NOT NULL,
                `currency`	INTEGER NOT NULL,
                `ctime`	INTEGER NOT NULL,
                `finished`	INTEGER NOT NULL,
                `date`	INTEGER NOT NULL,
                `note`	TEXT,
                FOREIGN KEY(`afrom`) REFERENCES Account(id),
                FOREIGN KEY(`ato`) REFERENCES Account(id),
                FOREIGN KEY(`creator`) REFERENCES User(id),
                FOREIGN KEY(`category`) REFERENCES `Category`(`id`),
                FOREIGN KEY(`currency`) REFERENCES `Currency`(`id`)
            );)"");
    }
    catch(sqlpp::exception e){
        logging::error(std::string("Error executing SQL statement:\n") + e.what());
    }
}
