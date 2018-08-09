//****************************************************************************
//**
//** Copyright (C) 2004-2008 IMPB RAS. All rights reserved.
//**
//** This file is part of the Vodoley.
//**
//** This file may be used under the terms of the GNU General Public
//** License version 2.0 as published by the Free Software Foundation
//** and appearing in the file LICENSE.GPL included in the packaging of
//** this file.
//**
//** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
//** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//**
//****************************************************************************/


#include "ui_dialog.h"

class Dialog : public QDialog, Ui::Dialog
{
	Q_OBJECT

public:
	Dialog(QWidget *parent = 0, Qt::WindowFlags fl = 0);
	~Dialog() {};

	int ASize() const { return BaseA->value(); }
	int BSize() const { return BaseB->value(); }
	int ANeed() const { return NeedA->value(); }

	void setSizes(int A, int B)
	{
		BaseA->setValue(A);
		BaseB->setValue(B);
	}

	int getStart() const
	{
		if (!taskNeeded->isChecked())
			return 0;
		return StartPos->value();
	}

	int getLeftBorder() const
	{
		if (!taskNeeded->isChecked())
			return 0;
		return spinBox->value();
	}

	int getRightBorder() const
	{
		if (!taskNeeded->isChecked())
			return 0;
		return spinBox_2->value();
	}

	void setLeftBorder(int pos)
	{
		spinBox->setValue(pos);
	}

	void setRightBorder(int pos)
	{
		spinBox_2->setValue(pos);
	}

	void setStart(int pos)
	{
		StartPos->setValue(pos);
	}

	QList<int> getFlags() const;
	void setFlags(const QList<int> &flags);

	bool borders() const { return Borders->isChecked(); }
	void setBordersChB(bool brd);

	bool isTaskNeeded() const { return taskNeeded->isChecked(); }
	void setTaskNeeded(bool task);

	void translateButtons();

public slots:
	void setMax();
	void addFlag();
	void enableDelete();
	void removeFlag();
};

