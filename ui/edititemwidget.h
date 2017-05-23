#ifndef EDITITEMWIDGET_H
#define EDITITEMWIDGET_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>

#include "util/itemsearcher.h"

class applyChangeStrategy;

namespace Ui {
class editItemWidget;
}

class editItemWidget : public QDialog
{
	Q_OBJECT

public:
	explicit editItemWidget(UserManager* userman, QWidget *parent = 0);
	~editItemWidget();
	QString getLabelText(int index);
	QString getLineEditText1();
	QString getLineEditText2();
	QString getComboboxText();
	QVector<QLabel*>* getlabelVector();
	void setApplyChangeStrategy(applyChangeStrategy* _apply);
	void setLabelName(QVector<QLabel*> & labelVector, const QStringList& namelist, const QVector<bool>& visiblelist);
	void setLineEdit2(const QString&defaultText = "", bool visible = true);
	void setLineEdit3(const QString&defaultText = "", bool visible = true);
	void setDeleteBtn(bool enabled = true);
	void setConformBtn(bool enabled = true);
	void setCancelBtn(bool enabled = true);
	void setCurrencyComboBox();

signals:
	void modified();

private slots:
	void on_deletebtn_clicked();

	void on_conformbtn_clicked();

private:
	UserManager* _userman;
	Ui::editItemWidget *ui;
	applyChangeStrategy* apply;
};

#endif // EDITITEMWIDGET_H
