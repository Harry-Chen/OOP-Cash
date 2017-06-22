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
 * @file   itemadder.cpp
 * @author Ice Coffee <ice438971718@gmail.com>
 * @date   2017.05
 * @brief  Implementation file of class ItemAdder
 */

#include "itemadder.h"
#include <QMessageBox>
#include <QJsonArray>
#include <QString>

ItemAdder::ItemAdder(QJsonObject & _obj, UserManager *_userman): obj(_obj), userman(_userman) {}

bool ItemAdder::additems() {
    if(!(obj.contains(key))) {
        QMessageBox::critical(nullptr, QObject::tr("导入失败"), QObject::tr("找不到 %1").arg(key));
        return false;
    }
    QJsonValue js_value = obj.take(key);
    if(!(js_value.isArray())) {
        QMessageBox::critical(nullptr, QObject::tr("导入失败"), QObject::tr("%1 格式错误").arg(key));
        return false;
    }
    QJsonArray js_array = js_value.toArray();

    int add_attempt = 0, add_success = 0;
    for(auto _item: js_array) {
        add_attempt++;
        if(_item.isObject()) {
            QJsonObject _itemObj = _item.toObject();
            add_success += add(_itemObj);
        }
    }
    QString message = QObject::tr("成功导入 %1 条\n文件内共 %2 条").arg(add_success).arg(add_attempt);
    QMessageBox::information(nullptr, QObject::tr("%1 导入成功").arg(key), message);
    return true;
}
