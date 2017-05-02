#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QString>
#include <QSettings>
#include <QApplication>
#include <QVariant>

class Configuration
{
public:
    static QVariant getConfiguration(const QString &key);
    static void setConfiguration(const QString &key, const QVariant &value);
    static QString getDatabasePath();
    static void setDatabasePath(const QString &path);
private:
    static QSettings mSettings;
};

#endif // CONFIGURATION_H