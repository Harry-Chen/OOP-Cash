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
 * @file   dataimporter.h
 * @author Ice Coffee <ice438971718@gmail.com>
 * @date   2017.05
 * @brief  Header file of class DataImporter
 */

#ifndef DATAIMPORTER_H
#define DATAIMPORTER_H
#include "dao/usermanager.h"
#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "accadder.h"
#include "curadder.h"
#include "catadder.h"
#include "billadder.h"

/**
 * @brief The DataImporter class
 */
class DataImporter {
private:
    UserManager * userman;
    QJsonObject obj;
    ItemAdder ** adder;

public:
    /**
     * @brief Initiate with UserManager*
     * @param _userman pointer of UserManager in charge of the User who has loggedin.
     */
    DataImporter(UserManager * _userman);
    /**
     * @brief doImport
     * @return Import succeeded or not
     */
    bool doImport();
};

#endif // DATAIMPORTER_H
