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
 * @file   dataimporter.cpp
 * @author Ice Coffee <ice438971718@gmail.com>
 * @date   2017.05
 * @brief  Implementation file of class DataImporter
 */

#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

#include "dataimporter.h"

DataImporter::DataImporter(UserManager *_userman): userman(_userman) {
    adder = new ItemAdder * [4];
    adder[0] = new CurAdder(obj, userman);
    adder[1] = new CatAdder(obj, userman);
    adder[2] = new AccAdder(obj, userman);
    adder[3] = new BillAdder(obj, userman);
}

bool DataImporter::doImport() {
    QString path;
    path = QFileDialog::getOpenFileName(nullptr, QObject::tr("选择导入文件"), "", QObject::tr("JS 对象标记 (*.json)"));
    if(path.isEmpty()) //User cancel
        return false;
    QFile inFile(path);
    if(!inFile.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(nullptr, QObject::tr("导入文件"), QObject::tr("无法打开文件:\n%1").arg(inFile.errorString()));
        return false;
    }
    QTextStream readin(&inFile);
    const QString &inputStr = readin.readAll();
    const QByteArray &inputByteArray = inputStr.toUtf8();

    QJsonParseError json_error;
    QJsonDocument parse_document = QJsonDocument::fromJson(inputByteArray, &json_error);
    if(json_error.error != QJsonParseError::NoError) {
        QMessageBox::critical(nullptr, QObject::tr("导入失败"), QObject::tr("发生了不可名状的错误>.<"));
        return false;
    }
    if(!parse_document.isObject()) {
        QMessageBox::critical(nullptr, QObject::tr("导入失败"), QObject::tr("导入文件格式有误哦>.<"));
        return false;
    }
    obj = parse_document.object();

    //add three arrays...
    for(int i=0; i<4; ++i) {
        if(!(adder[i]->additems()))
            return false;
    }
    QMessageBox::information(nullptr, QObject::tr("导入成功"), QObject::tr("快去查看自己的账单吧~！"));
    return true;
}


