#ifndef GUIQUERY_H
#define GUIQUERY_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include "dao/query.h"
#include "graphmainwindow.h"
#include

class GUIquery : public Query
{
     Q_OBJECT

    QMainWindow MainWindow;
    enum Type { } type;
public:
    //GUIquery();
    GUIquery (QMainWindow * _ui);

public slots:
    void getDateRange(const QDate &start, const QDate &end) { setDateRange(start, end); }
    void getFromAccount(ID _fromAccountId) { addFromAccountId(_fromAccountId); }
    void getToAccount(ID _toAccountId) { addToAccountId(_toAccountId); }
    void getFinished(bool _finished) { setFinished(_finished); }
    void getType (int _type) { type = _type; }
};

#endif // GUIQUERY_H
