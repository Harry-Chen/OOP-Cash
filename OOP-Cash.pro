#-------------------------------------------------
#
# Project created by QtCreator 2017-04-23T21:38:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = OOP-Cash
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp \
        libs\sqlite3.c \
        libs\logger.cpp \
        libs\qcustomplot.cpp \
    util/configuration.cpp \
    util/database_helper.cpp \
    dao/usermanager.cpp \
    dao/currencymanager.cpp \
    dao/categorymanager.cpp \
    dao/accountmanager.cpp \
    model/account.cpp \
    model/category.cpp \
    model/currency.cpp \
    model/user.cpp \
    model/bill.cpp \
    dao/billmanager.cpp \
    dao/query.cpp \
    datavisualization/mymainwindow.cpp \
    datavisualization/graphdock.cpp \
    datavisualization/querywidget.cpp \
    process/processor.cpp \
    process/processorfactory.cpp \
    ui/oopcash_mainwindow.cpp \
    ui/changebillwidget.cpp \
    ui/logindlg.cpp \
    ui/recordcostwidget.cpp \
    util/itemsearcher.cpp \
    ui/edititemwidget.cpp \
    ui/edititemwidgetfactory.cpp \
    ui/applyChangeStrategy/applychangestrategy.cpp \
    ui/applyChangeStrategy/editaccountstrategy.cpp \
    ui/applyChangeStrategy/editcategorystrategy.cpp \
    ui/applyChangeStrategy/editcurrencystrategy.cpp \
    ui/applyChangeStrategy/addaccountstrategy.cpp \
    ui/applyChangeStrategy/addcategorystrategy.cpp \
    ui/applyChangeStrategy/addcurrencystrategy.cpp
    ui/logindlg.cpp


INCLUDEPATH += include

debug:DEFINES += _DEBUG

win32{
    Debug:LIBS += $$PWD\libs\win_x64\sqlpp11-connector-sqlite3_debug.lib
    Release:LIBS += $$PWD\libs\win_x64\sqlpp11-connector-sqlite3_release.lib
}
macx{
    LIBS += $$PWD/libs/darwin_x64/libsqlpp11-connector-sqlite3.a
}

HEADERS  += \
    include\qcustomplot.h \
    database/tables.h \
    util/constants.h \
    util/configuration.h \
    util/database_helper.h \
    util/common.h \
    model/user.h \
    dao/usermanager.h \
    model/currency.h \
    dao/currencymanager.h \
    model/account.h \
    dao/accountmanager.h \
    model/bill.h \
    model/category.h \
    dao/categorymanager.h \
    dao/billmanager.h \
    dao/query.h \
    datavisualization/mymainwindow.h \
    datavisualization/graphdock.h \
    datavisualization/querywidget.h \
    ui/oopcash_mainwindow.h \
    ui/changebillwidget.h \
    ui/logindlg.h \
    ui/recordcostwidget.h \
    dao/itemmanager.h \
    util/itemsearcher.h \
    ui/edititemwidget.h \
    ui/edititemwidgetfactory.h \
    ui/applyChangeStrategy/applychangestrategy.h \
    ui/applyChangeStrategy/editaccountstrategy.h \
    ui/applyChangeStrategy/editcategorystrategy.h \
    ui/applyChangeStrategy/editcurrencystrategy.h \
    ui/applyChangeStrategy/addaccountstrategy.h \
    ui/applyChangeStrategy/addcategorystrategy.h \
    ui/applyChangeStrategy/addcurrencystrategy.h
    ui/logindlg.h

FORMS    += \
    datavisualization/graphdock.ui \
    datavisualization/mymainwindow.ui \
    datavisualization/querywidget.ui \
    ui/oopcash_mainwindow.ui \
    ui/changebillwidget.ui \
    ui/logindlg.ui \
    ui/edititemwidget.ui

RESOURCES += \
    uirsc.qrc
