//
// C++ Implementation: new task dialog
//
// Description:
//
//
// Author: Denis Khachko <mordol@lpm.org.ru>
//
// Copyright: See COPYING file that comes with this distribution
//

#include "dialog.h"
#include <QtGui>

Dialog::Dialog(QWidget *parent, Qt::WindowFlags fl):
	QDialog(parent, fl), Ui::Dialog()
{
	setupUi(this);
	connect(BaseA, SIGNAL(valueChanged(int)), this, SLOT(setMax()));
	connect(BaseB, SIGNAL(valueChanged(int)), this, SLOT(setMax()));
	connect(pushButton, SIGNAL(clicked()), this, SLOT(addFlag()));
	connect(pushButton_2, SIGNAL(clicked()), this, SLOT(removeFlag()));
	connect(listWidget, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(enableDelete()));
	translateButtons();
}

// Why?
void Dialog::setMax()
{
	int max = BaseA->value();
	if (BaseB->value() > max)
		max = BaseB->value();
}

void Dialog::enableDelete()
{
	pushButton_2->setEnabled(true);
}

void Dialog::addFlag()
{
	QList<QListWidgetItem *> flags = listWidget->findItems(
		NeedA->cleanText(), Qt::MatchExactly
	);

	if (flags.count() > 0)
		return;

	listWidget->addItem(NeedA->cleanText());
}

void Dialog::removeFlag()
{
	QList<QListWidgetItem *>  selectedItems = listWidget->selectedItems();
	qDebug() << "Item Count" << selectedItems.count();
	for (int i = 0; i < selectedItems.count(); i++) {
		listWidget->takeItem(listWidget->row(selectedItems[i]));
	}
	if (listWidget->selectedItems().count() == 0)
		pushButton_2->setEnabled(false);
}

QList<int> Dialog::getFlags() const
{
	QList<int> res;
	if (!taskNeeded->isChecked())
		return res;
	for (int i = 0; i < listWidget->count(); i++) {
		res.append(listWidget->item(i)->text().toInt());
	}
	return res;
}

void Dialog::setFlags(const QList<int> &flags)
{
	listWidget->clear();
	for (int i = 0; i < flags.count(); i++) {
		listWidget->addItem(QString::number(flags[i]));
	}
}

void Dialog::setBordersChB(bool brd)
{
	Borders->setChecked(brd);

	if (!brd)
		return;

	spinBox->setEnabled(true);
	spinBox_2->setEnabled(true);
}

void Dialog::setTaskNeeded(bool task)
{
	taskNeeded->setChecked(task);
	if (!task)
		return;
	frame_3->setEnabled(true);
	qDebug() << "frame_3->ENABLED!";
}

void Dialog::translateButtons()
{
	QList<QAbstractButton *>btns = buttonBox->buttons();
	for (int i = 0; i < btns.count(); i++) {
		if (buttonBox->buttonRole(btns[i]) == QDialogButtonBox::RejectRole)
			btns[i]->setText(trUtf8("Отмена"));
	}
}

