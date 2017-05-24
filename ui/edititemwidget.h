#ifndef EDITITEMWIDGET_H
#define EDITITEMWIDGET_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QMessageBox>

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
	editItemWidget* setApplyChangeStrategy(applyChangeStrategy* _apply);
	editItemWidget* setLabelName(QVector<QLabel*> & labelVector, const QStringList& namelist, const QVector<bool>& visiblelist);
	editItemWidget* setLineEdit2(const QString&defaultText = "", bool visible = true);
	editItemWidget* setLineEdit3(const QString&defaultText = "", bool visible = true);
	editItemWidget* setCurrencyComboBox(bool visible = true);
	editItemWidget* setDeleteBtn(bool enabled = true);
	editItemWidget* setConformBtn(bool enabled = true);
	editItemWidget* setCancelBtn(bool enabled = true);

signals:
	void modified();

private slots:
	void on_deletebtn_clicked();

	void on_conformbtn_clicked();

	void on_cancelbtn_clicked();

private:
	UserManager* _userman;
	Ui::editItemWidget *ui;
	applyChangeStrategy* apply;
};

#endif // EDITITEMWIDGET_H
