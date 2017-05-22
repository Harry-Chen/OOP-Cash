#include "dataexporter.h"
#include "util/database_helper.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

QJsonArray dataExporter::getJsArray(QVector<Bill> & _vectorBill)
{
    QJsonArray JsArBill;

    int i = 0;
    for(Bill theBill: _vectorBill) {
        QJsonObject jsO;
        jsO.insert("accFrom", accMap[theBill.from].name );
        jsO.insert("accTo", accMap[theBill.to].name);
        jsO.insert("catName", catMap[theBill.category].name);
        jsO.insert("curName", curMap[theBill.currency].name);
        jsO.insert("quantity", theBill.quantity);
        jsO.insert("finished", theBill.finished);
        jsO.insert("date", theBill.finished);
        jsO.insert("note", theBill.note);
        JsArBill.insert(i++,jsO);
    }
    return JsArBill;
}

dataExporter::dataExporter(UserManager *_userman): userman(_userman) {}

bool dataExporter::doExport() {
    accman = new AccountManager(userman);
    catman = new CategoryManager(userman);
    curman = new CurrencyManager(userman);
    userMap = userman->getAllItems();
    accMap = accman->getAllItems();
    catMap = catman->getAllItems();
    curMap = curman->getAllItems();
    exportBills = Query::newQuery(DatabaseHelper::getDb()).doQuery();

    auto &exportJsArray = getJsArray(exportBills);

    //output...
    QJsonDocument document;
    document.setArray(exportJsArray);
    QByteArray byte_array = document.toJson(QJsonDocument::Compact);
    QString outputStr(byte_array);

    QString path;
    while(path == "") {
        path = QFileDialog::getSaveFileName(nullptr, QObject::tr("选择导出路径"), "", QObject::tr("JS 对象标记 (*.json)"));
    }
    QFile outFile(path);
    if(!outFile.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(nullptr, "保存文件", "无法保存文件:\n" + outFile.errorString());
        return false;
    }
    QTextStream out(&outFile);
    out << outputStr;
    QMessageBox::information(nullptr, "导出", "导出成功!");
    return true;
}
