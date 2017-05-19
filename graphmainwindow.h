#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dao/query.h"

namespace Ui {
class GraphMainWindow;
}

class GraphMainWindow : public QMainWindow
{
    Q_OBJECT

/*
public slots:
    void getToDate(const QDate &date) ;
    void getFromAccount(ID _fromAccountId) { addFromAccountId(_fromAccountId); }
    void getToAccount(ID _toAccountId) { addToAccountId(_toAccountId); }
    void getFinished(bool _finished) { setFinished(_finished); }
    void getType (int _type) { type = _type; }
*/
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_timeTo_editingFinished();

    void on_timeFrom_dateChanged(const QDate &date);

    void on_timeTo_dateChanged(const QDate &date);

    void on_unfinished_stateChanged(int arg1);

    void on_Do_clicked();

private:
    Ui::MainWindow *ui;
    QDate startDate, endDate;
    bool _finished;
    bool _finishedSet = false;
    QString _noteKeyword;
    bool _noteKeywordSet = false;
    Query query;
};

#endif // MAINWINDOW_H
