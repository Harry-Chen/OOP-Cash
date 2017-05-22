#ifndef EDITACCOUNT_H
#define EDITACCOUNT_H

#include <QWidget>

namespace Ui {
class editAccount;
}

class editAccount : public QWidget
{
	Q_OBJECT

public:
	explicit editAccount(QWidget *parent = 0);
	~editAccount();

private:
	Ui::editAccount *ui;
};

#endif // EDITACCOUNT_H
