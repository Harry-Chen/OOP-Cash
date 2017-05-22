#include <QApplication>
#include <sqlpp11/sqlpp11.h>

#include "ui/oopcash_mainwindow.h"

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
	
    auto w = new OOPCash_MainWindow();
    w->show();

    return a.exec();
}

