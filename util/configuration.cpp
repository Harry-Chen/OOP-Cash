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
 * @file   configuration.cpp
 * @author Harry Chen <harry-chen@outlook.com>
 * @date   2017.05
 * @brief  Implementation file of class Configuration
 */

#include "util/configuration.h"

QSettings Configuration::mSettings(APP_ORGNIZATION, APP_NAME);

QVariant Configuration::getConfiguration(const QString &key)
{
    logging::trace(std::string() + "Get configuration key: " + key.toStdString());
    return mSettings.value(key);
}

void Configuration::setConfiguration(const QString &key, const QVariant &value)
{
    logging::trace(std::string() + "Set configuration key: " + key.toStdString() + ", value: " + value.toString().toStdString());
    mSettings.setValue(key, value);
}

QString Configuration::getDatabasePath()
{
    QVariant path = getConfiguration(CONFIG_KEY_DATABASE_LOCATION);
    if(path.isNull()) return "";
    else return path.value<QString>();
}

void Configuration::setDatabasePath(const QString &path)
{
    setConfiguration(CONFIG_KEY_DATABASE_LOCATION, path);
}
