#include "dataexporter.h"
#include "util/database_helper.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

QJsonArray dataExporter::getCurrencyArray(){
    QJsonArray arrayOfCurrency;
    for(const Currency &c : curMap.values()){
        QJsonObject o;
        o.insert("name", c.name);
        o.insert("rate", QString::number(c.rate));
        arrayOfCurrency.append(o);
    }
    return arrayOfCurrency;
}

QJsonArray dataExporter::getAccountArray(){
    QJsonArray arrayOfAccount;
    for(const Account &a : accMap.values()){
        QJsonObject o;
        o.insert("name", a.name);
        o.insert("currency", curMap[a.cid].name);
        arrayOfAccount.append(o);
    }
    return arrayOfAccount;
}

QJsonArray dataExporter::getBillArray(QVector<Bill> & _vectorBill)
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

dataExporter::dataExporter(UserManager *_userman): userman(_userman) {}

bool dataExporter::doExport() {
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
    const auto &exportJsArray = getBillArray(exportBills);
    QJsonObject object;
    object.insert("currency", arrayOfCurrency);
    object.insert("account", arrayOfAccount);
    object.insert("bills", exportJsArray);
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
        QMessageBox::warning(nullptr, "保存文件", "无法保存文件:\n" + outFile.errorString());
        return false;
    }
    QTextStream out(&outFile);
    out << outputStr;
    QMessageBox::information(nullptr, "导出", "导出成功!");
    return true;
}
