#ifndef CALENDARDIALOG_H
#define CALENDARDIALOG_H

#include <QDialog>

namespace Ui {
class CalendarDialog;
}

class CalendarDialog : public QDialog
{
	Q_OBJECT

public:
	explicit CalendarDialog(QWidget *parent = 0);
	QDate getSelectedDate();
	~CalendarDialog();
signals:
	void seletedDateChanged();
    //void dateClicked(QDate);
private slots:
	void on_conformBtn_clicked();

public:
	Ui::CalendarDialog *ui;
};

#endif // CALENDARDIALOG_H
