#include "dataimporter.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

dataImporter::dataImporter(UserManager *_userman): userman(_userman) {
    adder = new itemAdder * [4];
    adder[0] = new curAdder(obj, userman);
    adder[1] = new catAdder(obj, userman);
    adder[2] = new accAdder(obj, userman);
    adder[3] = new billAdder(obj, userman);
}

bool dataImporter::doImport() {
    QString path;
    path = QFileDialog::getOpenFileName(nullptr, QObject::tr("选择导入文件"), "", QObject::tr("JS 对象标记 (*.json)"));
    if(path.isEmpty()) //User cancel
        return false;
    QFile inFile(path);
    if(!inFile.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(nullptr, "导入文件", "无法打开文件:\n" + inFile.errorString());
        return false;
    }
    QTextStream readin(&inFile);
    QString &inputStr = readin.readAll();
    QByteArray &inputByteArray = inputStr.toUtf8();

    QJsonParseError json_error;
    QJsonDocument parse_document = QJsonDocument::fromJson(inputByteArray, &json_error);
    if(json_error.error != QJsonParseError::NoError) {
        QMessageBox::critical(nullptr, "导入失败", "发生了不可名状的错误>.<");
        return false;
    }
    if(!parse_document.isObject()) {
        QMessageBox::critical(nullptr, "导入失败", "导入文件格式有误哦>.<");
        return false;
    }
    obj = parse_document.object();

    //add three arrays...
    for(int i=0; i<4; ++i) {
        if(!(adder[i]->additems()))
            return false;
    }
    QMessageBox::information(nullptr, "导入成功", "快去查看自己的账单吧~！");
    return true;
}


