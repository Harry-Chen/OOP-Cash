#ifndef USERSETDIALOG_H
#define USERSETDIALOG_H

#include <QDialog>

namespace Ui {
class userSetDialog;
}

class userSetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit userSetDialog(QWidget *parent = 0);
    ~userSetDialog();

private:
    Ui::userSetDialog *ui;
};

#endif // USERSETDIALOG_H
