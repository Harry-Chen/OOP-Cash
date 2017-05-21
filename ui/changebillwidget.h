#ifndef CHANGEBILLWIDGET_H
#define CHANGEBILLWIDGET_H

#include <QWidget>

namespace Ui {
class ChangeBillWidget;
}

class ChangeBillWidget : public QWidget
{
	Q_OBJECT

public:
	explicit ChangeBillWidget(QWidget *parent = 0);
	~ChangeBillWidget();

protected:
	Ui::ChangeBillWidget *ui;
};

#endif // CHANGEBILLWIDGET_H
