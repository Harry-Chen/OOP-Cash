#include "util/configuration.h"
#include "util/constants.h"

QSettings Configuration::mSettings(APP_ORGNIZATION, APP_NAME);

QVariant Configuration::getConfiguration(const QString &key)
{
    return mSettings.value(key);
}

void Configuration::setConfiguration(const QString &key, const QVariant &value)
{
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
