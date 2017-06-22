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
 * @file   itemadder.h
 * @author Ice Coffee <ice438971718@gmail.com>
 * @date   2017.05
 * @brief  Header file of class ItemAdder
 */

#ifndef ITEMADDER_H
#define ITEMADDER_H
#include "dao/usermanager.h"
#include <QString>
#include <QJsonObject>

/**
 * @brief Abstract adder of items
 */
class ItemAdder
{
protected:
    /**
     * @brief key the name of concrete item
     */
    QString key;
    QJsonObject &obj;
    UserManager* userman;

public:
    /**
     * @brief Initiate with QJsonObject& and UserManager*
     * @param _obj reference to the QJsonObject of DataImporter
     * @param _userman pointer of UserManager in charge of the User who has loggedin.
     */
    ItemAdder(QJsonObject & _obj, UserManager* _userman);
    /**
     * @brief the frame of adding items
     * @return succeeded or not
     */
    bool additems();
    /**
     * @brief virtual function to add one item
     * @param _item the item in type of QJsonObject
     * @return succeeded or not
     */
    virtual bool add(QJsonObject  _item) = 0;
};

#endif // ITEMADDER_H
