#ifndef EDITITEMWIDGET_H
#define EDITITEMWIDGET_H

#include <QDialog>

namespace Ui {
class editItemWidget;
}

class editItemWidget : public QDialog
{
	Q_OBJECT

public:
	explicit editItemWidget(QWidget *parent = 0);
	~editItemWidget();

private:
	Ui::editItemWidget *ui;
};

#endif // EDITITEMWIDGET_H
