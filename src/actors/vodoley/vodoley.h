//****************************************************************************
//**
//** Copyright (C) 2004-2008 IMPB RAS. All rights reserved.
//**
//** This file is part of the KuMir.
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

#ifndef VODOLEY_H
#define VODOLEY_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMutex>

class QToolButton;
class QLabel;
class QFrame;

class pultLogger;
class VodoleyPult;
class Vial;

class Vodoley: public QMainWindow
{
	Q_OBJECT

public:
	Vodoley();
	~Vodoley();

	uint CurA() const { return Curfill[0]; }
	uint CurB() const { return Curfill[1]; }
	uint CurC() const { return Curfill[2]; }

	bool isReady() const
	{
		return ((CurA() == AfillR) || (CurB() == AfillR) || (CurC() == AfillR)) ;
	}

	uint Asize() const { return Maxfill[0]; }
	uint Bsize() const { return Maxfill[1]; }
	uint Csize() const { return Maxfill[2]; }

	uint maxSize() const
	{
		uint max = 1;
		if (max < Asize())
			max = Asize();
		if (max < Bsize())
			max = Bsize();
		if (max < Csize())
			max = Csize();

		return max;
	}

	bool loadIoDevice(QIODevice *source);
	bool loadFile(QString fileName);

	void AutoClose()
	{
		autoClose = true;
		setVisible(false);
	}

	void createActions(QList<QAction *> actions);

protected:
	void mousePressEvent(QMouseEvent *event);
	void resizeEvent(QResizeEvent *event);

public slots:
	void reset();

	void newZ();
	void loadZ();
	void saveZ();

	void FillA();
	void FillB();
	void FillC();

	void MoveFromTo(uint from, uint to);
	void redraw();

signals:
	void Otkaz(QString msg);
	void Ok();
	void CNull();
	void CNotNull();
	void FileLoaded(QString fname);

public:
	VodoleyPult *pult;

private:
	void setBaseFill(int A, int B, int C)
	{
		Curfill[0] = A;
		Curfill[1] = B;
		Curfill[2] = C;
	}

	void updateMenzur();
	void updateNeedBirka();

	void CreateVodoley();
	void CreateDummyTask();

private:
	QAction *actNew, *actLoad, *actSave;

	QGraphicsScene *scene;
	QGraphicsView *view;
	pultLogger *logger;
	QGraphicsSimpleTextItem *Atext, *Btext, *Ctext;
	QLabel *needLabel;
	QFrame *needFrame;

	uint Afill, Bfill, Cfill; //Сколько  налито изначально
	QList<uint> Curfill; //Сколько сейчас налито
	QList<uint> Maxfill; //Размер емкости
	uint AfillR, BfillR, CfillR; //Сколько должно быть

	Vial *Amen, *Bmen, *Cmen;
	QMutex mutex;
	QString curDir;
	bool autoClose;
};

#endif
