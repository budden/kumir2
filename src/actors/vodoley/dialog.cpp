//
// C++ Implementation: VodoleyDialog
//
// Description:
//
//
// Author: Denis Khachko <mordol@mail.ru>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "dialog.h"
#include <QToolButton>


Dialog::Dialog(QWidget* parent, Qt::WindowFlags fl ):
	QDialog (parent, fl), Ui::Dialog()
{
	setupUi(this);
	connect(BaseA, SIGNAL(valueChanged(int)), this, SLOT(setMax()));
	connect(BaseB, SIGNAL(valueChanged(int)), this, SLOT(setMax()));
	connect(BaseC, SIGNAL(valueChanged(int)), this, SLOT(setMax()));
	translateButtons();
	setMax();
}

void Dialog::setMax()
{
	ValueA->setMaximum(BaseA->value());
	ValueB->setMaximum(BaseB->value());
	ValueC->setMaximum(BaseC->value());

	int max = BaseA->value();
	if (BaseB->value() > max)
		max = BaseB->value();
	if (BaseC->value() > max)
		max = BaseC->value();

	NeedA->setMaximum(max);
}

void Dialog::translateButtons()
{
	QList<QAbstractButton *>btns = buttonBox->buttons();
	for (int i = 0; i < btns.count(); i++) {
		if (buttonBox->buttonRole(btns[i]) == QDialogButtonBox::RejectRole)
			btns[i]->setText(trUtf8("Отмена"));
	}
}

