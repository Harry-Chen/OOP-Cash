#include "itemadder.h"
#include <QMessageBox>
#include <QJsonArray>
#include <QString>

itemAdder::itemAdder(QJsonObject & _obj, UserManager *_userman): obj(_obj), userman(_userman) {}

bool itemAdder::additems() {
    if(!(obj.contains(key))) {
        QMessageBox::critical(nullptr, "导入失败", "找不到" + key);
        return false;
    }
    QJsonValue js_value = obj.take(key);
    if(!(js_value.isArray())) {
        QMessageBox::critical(nullptr, "导入失败", key + "格式错误");
        return false;
    }
    QJsonArray js_array = js_value.toArray();

    int add_attempt = 0, add_success = 0;
    for(auto _item: js_array) {
        add_attempt++;
        if(_item.isObject())
            add_success += add(_item.toObject());
    }
    QMessageBox::information(nullptr, "导入成功" + key, "成功导入 " + QString::number(add_success) + "条\n文件内共 " + QString::number(add_attempt) + "条" );
    return true;
}
