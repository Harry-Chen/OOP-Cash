#include <QApplication>
#include <QDebug>
#include <sqlpp11/sqlpp11.h>

#include "util/common.h"
#include "util/database_helper.h"
#include "dao/usermanager.h"
#include "model/user.h"

namespace sql = sqlpp::sqlite3;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    logging::Logger::instance().setLogDir(QCoreApplication::applicationDirPath().toStdString());
    logging::Logger::instance().setLogFilePrefix(APP_NAME.toStdString());
#ifdef _DEBUG
    logging::Logger::instance().setMinLevel(logging::l_trace);
#else
    logging::Logger::instance().setMinLevel(logging::l_info);
#endif


    logging::trace("Application Start===========");

    DatabaseHelper::initializeDatabase();
\
    User newUser(-1, "Test", "Test Test");
    newUser.setPassword("1234");
    UserManager::addUser(newUser);
    QVector<User> lists = UserManager::getAllUsers();
    UserManager::login(newUser);
    UserManager::modifyInfo(newUser, newUser);
    UserManager::removeUser(newUser);

    logging::trace("Application End===========");
    return 0;
}
