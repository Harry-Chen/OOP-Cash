#ifndef BILLLIST_H
#define BILLLIST_H

#include <QListWidget>
#include <QScrollBar>
#include <QDebug>

class BillList : public QListWidget
{
	Q_OBJECT
public:
	explicit BillList(QWidget *parent = 0);

public slots:
	void setIsAddingFalse();
	void setFinished(bool finished);

signals:
	void needAdding();

private slots:
	void on_scroll_bar_value_changed(int value);

private:
	QScrollBar* _scrollBar;
	bool isAdding;
	bool allFinished;
};

#endif // BILLLIST_H
