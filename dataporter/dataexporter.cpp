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
 * @file   dataexporter.cpp
 * @author Ice Coffee <ice438971718@gmail.com>
 * @date   2017.05
 * @brief  Implementation file of class DataExporter
 */

#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

#include "dataexporter.h"
#include "util/database_helper.h"

QJsonArray DataExporter::getCurrencyArray(){
    QJsonArray arrayOfCurrency;
    for(const Currency &c : curMap.values()){
        QJsonObject o;
        o.insert("name", c.name);
        o.insert("rate", QString::number(c.rate));
        arrayOfCurrency.append(o);
    }
    return arrayOfCurrency;
}

QJsonArray DataExporter::getAccountArray(){
    QJsonArray arrayOfAccount;
    for(const Account &a : accMap.values()){
        QJsonObject o;
        o.insert("name", a.name);
        o.insert("currency", curMap[a.cid].name);
        arrayOfAccount.append(o);
    }
    return arrayOfAccount;
}

QJsonArray DataExporter::getCategoryArray()
{
    QJsonArray arrayOfCategory;
    for(const Category &c : catMap.values()){
        QJsonObject o;
        o.insert("name", c.name);
        arrayOfCategory.append(o);
    }
    return arrayOfCategory;
}

QJsonArray DataExporter::getBillArray(QVector<Bill> & _vectorBill)
{
    QJsonArray arrayOfBill;

    for(const Bill& theBill: _vectorBill) {
        QJsonObject jsO;
        jsO.insert("accFrom", theBill.from != -1 ? accMap[theBill.from].name : "-1");
        jsO.insert("accTo", theBill.to != -1 ? accMap[theBill.to].name : "-1");
        jsO.insert("catName", theBill.category != -1 ? catMap[theBill.category].name : "-1");
        jsO.insert("curName", curMap[theBill.currency].name);
        jsO.insert("quantity", theBill.quantity);
        jsO.insert("finished", theBill.finished);
        jsO.insert("date", theBill.date.toString("yyyy-MM-dd"));
        jsO.insert("note", theBill.note);
        arrayOfBill.append(jsO);
    }
    return arrayOfBill;
}

DataExporter::DataExporter(UserManager *_userman): userman(_userman) {}

bool DataExporter::doExport() {
    accman = new AccountManager(userman);
    catman = new CategoryManager(userman);
    curman = new CurrencyManager(userman);
    userMap = userman->getAllItems();
    accMap = accman->getAllItems();
    catMap = catman->getAllItems();
    curMap = curman->getAllItems();
    exportBills = Query::newQuery(DatabaseHelper::getDb())
            .addCreatorId(userman->getLoggedInUid())
            .doQuery();

    const auto &arrayOfCurrency = getCurrencyArray();
    const auto &arrayOfAccount = getAccountArray();
    const auto &arrayOfCategory = getCategoryArray();
    const auto &arrayOfBill = getBillArray(exportBills);
    QJsonObject object;
    object.insert("currency", arrayOfCurrency);
    object.insert("category", arrayOfCategory);
    object.insert("account", arrayOfAccount);
    object.insert("bills", arrayOfBill);
    //output...
    QJsonDocument document;
    document.setObject(object);
    QByteArray byte_array = document.toJson(QJsonDocument::Indented);
    QString outputStr(byte_array);

    QString path;
    path = QFileDialog::getSaveFileName(nullptr, QObject::tr("选择导出路径"), "", QObject::tr("JS 对象标记 (*.json)"));
    if(path.isEmpty()) //User cancel
        return false;
    QFile outFile(path);
    if(!outFile.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(nullptr, QObject::tr("保存文件"), QObject::tr("无法保存文件:\n%1").arg(outFile.errorString()));
        return false;
    }
    QTextStream out(&outFile);
    out << outputStr;
    QMessageBox::information(nullptr, QObject::tr("导出"), QObject::tr("导出成功!"));
    return true;
}
