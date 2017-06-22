QT       += core gui widgets printsupport

TARGET = OOP-Cash
TEMPLATE = app

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += include

PRECOMPILED_HEADER += util/common.h

TRANSLATIONS += lang/en_US.ts

debug:DEFINES += _DEBUG

win32{
    Debug:LIBS += $$PWD\libs\win_x64\sqlpp11-connector-sqlite3_debug.lib
    Release:LIBS += $$PWD\libs\win_x64\sqlpp11-connector-sqlite3_release.lib
}
macx{
    LIBS += $$PWD/libs/darwin_x64/libsqlpp11-connector-sqlite3.a
}

SOURCES += main.cpp \
        libs/sqlite3.c \
        libs/logger.cpp \
        libs/qcustomplot.cpp \
    util/configuration.cpp \
    util/database_helper.cpp \
    util/itemsearcher.cpp \
    model/account.cpp \
    model/category.cpp \
    model/currency.cpp \
    model/user.cpp \
    model/bill.cpp \
    dao/usermanager.cpp \
    dao/currencymanager.cpp \
    dao/categorymanager.cpp \
    dao/accountmanager.cpp \
    dao/billmanager.cpp \
    dao/query.cpp \
    datavisualization/graphdock.cpp \
    datavisualization/querywidget.cpp \
    ui/oopcash_mainwindow.cpp \
    ui/changebillwidget.cpp \
    ui/logindlg.cpp \
    ui/usersetdlg.cpp \
    ui/billdetailwidget.cpp \
    ui/detailwidget.cpp \
    ui/edititemwidget.cpp \
    ui/edititemwidgetfactory.cpp \
    ui/calendardialog.cpp \
    ui/dateeditcalendar.cpp \
    ui/recordcostearnwidget.cpp \
    ui/applyChangeStrategy/applychangestrategy.cpp \
    ui/applyChangeStrategy/editaccountstrategy.cpp \
    ui/applyChangeStrategy/editcategorystrategy.cpp \
    ui/applyChangeStrategy/editcurrencystrategy.cpp \
    ui/applyChangeStrategy/addaccountstrategy.cpp \
    ui/applyChangeStrategy/addcategorystrategy.cpp \
    ui/applyChangeStrategy/addcurrencystrategy.cpp \
    dataporter/dataexporter.cpp \
    dataporter/dataimporter.cpp \
    dataporter/itemadder.cpp \
    dataporter/accadder.cpp \
    dataporter/billadder.cpp \
    dataporter/curadder.cpp \
    dataporter/catadder.cpp \  
    plot/processor/processor.cpp \
    plot/billsplotsystem.cpp \
    plot/processor/billsprocessor.cpp \
    plot/processor/balanceprocessor.cpp \
    plot/plotter/lineplotter.cpp \
    plot/balanceplotsystem.cpp \
    plot/plotter/barplotter.cpp

HEADERS  += \
    include/qcustomplot.h \
    database/tables.h \
    util/constants.h \
    util/configuration.h \
    util/database_helper.h \
    util/common.h \
    util/itemsearcher.h \
    model/user.h \
    model/currency.h \
    model/account.h \
    model/bill.h \
    model/category.h \
    dao/itemmanager.h \
    dao/usermanager.h \
    dao/currencymanager.h \
    dao/accountmanager.h \
    dao/categorymanager.h \
    dao/billmanager.h \
    dao/query.h \
    datavisualization/graphdock.h \
    datavisualization/querywidget.h \
    ui/oopcash_mainwindow.h \
    ui/changebillwidget.h \
    ui/logindlg.h \
    ui/usersetdlg.h \
    ui/billdetailwidget.h \
    ui/detailwidget.h \
    ui/calendardialog.h \
    ui/dateeditcalendar.h \
    ui/edititemwidget.h \
    ui/edititemwidgetfactory.h \
    ui/recordcostearnwidget.h \
    ui/applyChangeStrategy/applychangestrategy.h \
    ui/applyChangeStrategy/editaccountstrategy.h \
    ui/applyChangeStrategy/editcategorystrategy.h \
    ui/applyChangeStrategy/editcurrencystrategy.h \
    ui/applyChangeStrategy/addaccountstrategy.h \
    ui/applyChangeStrategy/addcategorystrategy.h \
    ui/applyChangeStrategy/addcurrencystrategy.h \
    dataporter/dataexporter.h \
    dataporter/dataimporter.h \
    dataporter/itemadder.h \
    dataporter/accadder.h \
    dataporter/billadder.h \
    dataporter/curadder.h \
    dataporter/catadder.h \
    plot/plotsystem.h \
    plot/plotter/plotter.h \
    plot/processor/processor.h \
    plot/billsplotsystem.h \
    plot/processor/billsprocessor.h \
    plot/processor/balanceprocessor.h \
    plot/plotter/barplotter.h \
    plot/plotter/lineplotter.h \
    plot/balanceplotsystem.h
	
FORMS    += \
    datavisualization/graphdock.ui \
    datavisualization/querywidget.ui \
    ui/oopcash_mainwindow.ui \
    ui/changebillwidget.ui \
    ui/usersetdialog.ui \
    ui/billdetailwidget.ui \
    ui/detailwidget.ui \
    ui/logindlg.ui \
    ui/edititemwidget.ui \
    ui/calendardialog.ui \
    ui/dateeditcalendar.ui

RESOURCES += \
    uirsc.qrc
