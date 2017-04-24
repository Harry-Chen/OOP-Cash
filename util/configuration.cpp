#include "util/configuration.h"
#include "util/common.h"

QSettings Configuration::mSettings(APP_ORGNIZATION, APP_NAME);

QVariant Configuration::getConfiguration(const QString &key)
{
    logging::trace(std::string() + "Get configuration key: " + key.toStdString());
    return mSettings.value(key);
}

void Configuration::setConfiguration(const QString &key, const QVariant &value)
{
    logging::trace(std::string() + "Set configuration key: " + key.toStdString() + ", value: " + value.toString().toStdString());
    mSettings.setValue(key, value);
}

QString Configuration::getDatabasePath()
{
    QVariant path = getConfiguration(CONFIG_KEY_DATABASE_LOCATION);
    if(path.isNull()) return "";
    else return path.value<QString>();
}

void Configuration::setDatabasePath(const QString &path)
{
    setConfiguration(CONFIG_KEY_DATABASE_LOCATION, path);
}
