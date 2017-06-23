/**
 * @file   main.cpp
 * @author Harry Chen <harry-chen@outlook.com>
 * @date   2017.05
 * @brief  Main entrance of the program
 */

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
	
    //The qm file need to be put in the working directory of the program
    QTranslator translator;
    translator.load("en_US.qm");
    a.installTranslator(&translator);

	logging::trace("Application Start===========");
    DatabaseHelper::initializeDatabase();
	
    //apply QSS
    QString styleSheet;
    auto* qssFile = new QFile(":/qss/stylesheet");
    if(qssFile->open(QFile::ReadOnly)) {
        styleSheet = QString(qssFile->readAll());
        qApp->setStyleSheet(styleSheet);
        qssFile->close();
    }

    auto w = new OOPCash_MainWindow();
    w->show();

    return a.exec();
}
