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
 * @file   configuration.h
 * @author Harry Chen <harry-chen@outlook.com>
 * @date   2017.05
 * @brief  Header file of class Configuration
 */
#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QString>
#include <QSettings>
#include <QApplication>
#include <QVariant>
#include "util/constants.h"
#include "logging/logger.h"

#pragma execution_character_set("utf-8")

/**
 * @brief The basic configuration of the program
 */
class Configuration
{
public:
    /**
     * @param key the name of key
     * @return the value of configuration
     */
    static QVariant getConfiguration(const QString &key);
    /**
     * @param key the name of key
     * @param value the value
     */
    static void setConfiguration(const QString &key, const QVariant &value);
    /**
     * @return the path of database (can be empty)
     */
    static QString getDatabasePath();
    /**
     * @param path the path to set
     */
    static void setDatabasePath(const QString &path);
private:
    static QSettings mSettings;
};

#endif // CONFIGURATION_H
