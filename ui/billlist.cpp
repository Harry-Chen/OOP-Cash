#include "billlist.h"

BillList::BillList(QWidget *parent) : QListWidget(parent)
{
	isAdding = false;
	allFinished = false;
	_scrollBar = this->verticalScrollBar();
	connect(_scrollBar, SIGNAL(valueChanged(int)), this, SLOT(on_scroll_bar_value_changed(int)));
}

void BillList::setIsAddingFalse()
{
	isAdding = false;
}

void BillList::setFinished(bool finished)
{
	allFinished = finished;
}

void BillList::on_scroll_bar_value_changed(int value)
{
	if(!allFinished && !isAdding && value == _scrollBar->maximum()) {
		isAdding = true;
		emit needAdding();
	}
}
