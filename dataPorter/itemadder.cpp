#include "itemadder.h"
#include <QMessageBox>
#include <QJsonArray>
#include <QString>

itemAdder::itemAdder(QJsonObject & _obj, UserManager *_userman): obj(_obj), userman(_userman) {}

bool itemAdder::additems() {
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
