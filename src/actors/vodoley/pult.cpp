/****************************************************************************
**
** Copyright (C) 2004-2008 NIISI RAS. All rights reserved.
**
** This file is part of the KuMir.
**
** This file may be used under the terms of the GNU General Public
** License version 2.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of
** this file.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#include "vodoley.h"
#include "pult.h"
#include <kumir2-libs/widgets/pultlogger.h>

#include "vodoleymodule.h"
#define TEXT_STEP 14


VodoleyPult::VodoleyPult(QWidget *parent, Qt::WindowFlags fl)
	: QWidget(parent, fl), Ui::VodoleyPult()
{
	autoClose = false;
	setupUi(this);
	this->setMinimumSize(QSize(250, 400));

	Logger = new pultLogger(ActorVodoley::VodoleyModule::self->myResourcesDir(), this);


	this->setMinimumSize(250, 450);
	Logger->setSizes(164, 150);
	Logger->Move(40, 5);
	greenLight = new linkLight(this);
	greenLight->move(15, 29);
	greenLight->resize(12, 104);

	UpB->hide();
	BtoC = new MainButton(ActorVodoley::VodoleyModule::self->myResourcesDir(), this);

	BtoC->setGeometry(UpB->geometry());
	BtoC->setText(" ");
	BtoC->loadIcon(ActorVodoley::VodoleyModule::self->myResourcesDir().absoluteFilePath("b2c.png"));

	DownB->hide();
	buttBack = new MainButton(ActorVodoley::VodoleyModule::self->myResourcesDir(), this);
	buttBack->move(DownB->pos());
	buttBack->setGeometry(DownB->geometry());
	buttBack->setText(" ");
	buttBack->loadIcon(ActorVodoley::VodoleyModule::self->myResourcesDir().absoluteFilePath("bout.png"));

	AtoCb->hide();
	AtoC = new MainButton(ActorVodoley::VodoleyModule::self->myResourcesDir(), this);
	AtoC->setGeometry(AtoCb->geometry());
	AtoC->setText(" ");
	AtoC->loadIcon(ActorVodoley::VodoleyModule::self->myResourcesDir().absoluteFilePath("a2c.png"));

	AoutB->hide();
	turnRight = new MainButton(ActorVodoley::VodoleyModule::self->myResourcesDir(), this);
	turnRight->setGeometry(AoutB->geometry());
	turnRight->setText(" ");
	turnRight->loadIcon(ActorVodoley::VodoleyModule::self->myResourcesDir().absoluteFilePath("aout.png"));
	CoutB->hide();
	Coutb = new MainButton(ActorVodoley::VodoleyModule::self->myResourcesDir(), this);
	Coutb->setGeometry(CoutB->geometry());
	Coutb->setText(" ");
	Coutb->loadIcon(ActorVodoley::VodoleyModule::self->myResourcesDir().absoluteFilePath("cout.png"));

	askFree = new MainButton(ActorVodoley::VodoleyModule::self->myResourcesDir(), this);
	askFree->setCheckable(true);
	askFree->setText(trUtf8(" "));
	askFree->loadIcon(ActorVodoley::VodoleyModule::self->myResourcesDir().absoluteFilePath("svobodno.png"));
	askFree->setCheckable(true);
	askFree->hide();

	AtoBb->hide();
	AtoB = new MainButton(ActorVodoley::VodoleyModule::self->myResourcesDir(), this);
	AtoB->setGeometry(AtoBb->geometry());
	AtoB->setText(trUtf8(" "));
	if (!AtoB->loadIcon(ActorVodoley::VodoleyModule::self->myResourcesDir().absoluteFilePath("a2b.png"))) {
		qWarning("Image not loaded!");
	}

	CtoBb->hide();
	CtoB = new MainButton(ActorVodoley::VodoleyModule::self->myResourcesDir(), this);
	CtoB->setGeometry(CtoBb->geometry());
	CtoB->setText(trUtf8(" "));
	if (!CtoB->loadIcon(ActorVodoley::VodoleyModule::self->myResourcesDir().absoluteFilePath("c2b.png"))) {
		qWarning("Image not loaded!");
	}

	CtoAb->hide();
	CtoA = new MainButton(ActorVodoley::VodoleyModule::self->myResourcesDir(), this);
	CtoA->setGeometry(CtoAb->geometry());
	CtoA->setText(trUtf8(" "));
	if (!CtoA->loadIcon(ActorVodoley::VodoleyModule::self->myResourcesDir().absoluteFilePath("c2a.png"))) {
		qWarning("Image not loaded!");
	}

	TempB->hide();
	buttTemp = new MainButton(ActorVodoley::VodoleyModule::self->myResourcesDir(), this);
	buttTemp->setGeometry(TempB->geometry());

	buttTemp->setText(" ");
	buttTemp->loadIcon(ActorVodoley::VodoleyModule::self->myResourcesDir().absoluteFilePath("b2a.png"));

	QIcon toKumirIco(ActorVodoley::VodoleyModule::self->myResourcesDir().absoluteFilePath("kumir.png"));
	toKumir->setIcon(toKumirIco);
	toKumir->setEnabled(true);
	ClearLog->setIcon(QIcon(ActorVodoley::VodoleyModule::self->myResourcesDir().absoluteFilePath("edit-delete.png")));


	FillA->hide();
	aFill = new MainButton(ActorVodoley::VodoleyModule::self->myResourcesDir(), this);
	aFill->setText(trUtf8(" "));
	aFill->loadIcon(ActorVodoley::VodoleyModule::self->myResourcesDir().absoluteFilePath("afill.png"));
	aFill->setGeometry(FillA->geometry());

	FillB->hide();
	bFill = new MainButton(ActorVodoley::VodoleyModule::self->myResourcesDir(), this);
	bFill->setText(trUtf8(" "));
	bFill->loadIcon(ActorVodoley::VodoleyModule::self->myResourcesDir().absoluteFilePath("bfill.png"));
	bFill->setGeometry(FillB->geometry());

	FillC->hide();
	cFill = new MainButton(ActorVodoley::VodoleyModule::self->myResourcesDir(), this);
	cFill->setText(trUtf8(" "));
	cFill->loadIcon(ActorVodoley::VodoleyModule::self->myResourcesDir().absoluteFilePath("cfill.png"));
	cFill->setGeometry(FillC->geometry());

	connect(BtoC, SIGNAL(clicked()), this, SLOT(Up()));

	connect(buttBack, SIGNAL(clicked()), this, SLOT(BOutS()));
	connect(AtoC, SIGNAL(clicked()), this, SLOT(AtoCS()));
	connect(turnRight, SIGNAL(clicked()), this, SLOT(AOutS()));
	connect(Coutb, SIGNAL(clicked()), this, SLOT(COutS()));

	connect(AtoB, SIGNAL(clicked()), this, SLOT(AtoBS()));
	connect(CtoB, SIGNAL(clicked()), this, SLOT(CtoBS()));
	connect(CtoA, SIGNAL(clicked()), this, SLOT(CtoAS()));

	connect(buttTemp, SIGNAL(clicked()), this, SLOT(TempS()));

	connect(ClearLog, SIGNAL(clicked()), Logger, SLOT(ClearLog()));
	connect(ClearLog, SIGNAL(clicked()), this, SLOT(resetVodoley()));

	connect(aFill, SIGNAL(clicked()), this, SLOT(FillAs()));
	connect(bFill, SIGNAL(clicked()), this, SLOT(FillBs()));
	connect(cFill, SIGNAL(clicked()), this, SLOT(FillCs()));
	connect(toKumir, SIGNAL(clicked()), this, SLOT(logToKumir()));

	link = true;
}


void VodoleyPult::noLink()
{
	link = false;
	greenLight->setLink(link);
	greenLight->repaint();
	qWarning("NoLINK");
	ClearLog->setEnabled(false);
	toKumir->setEnabled(false);
}
void VodoleyPult::LinkOK()
{
	qDebug() << "LinkOK";
	link = true;
	greenLight->setLink(link);
	greenLight->repaint();
	ClearLog->setEnabled(true);
	toKumir->setEnabled(true);
};

void VodoleyPult::Up()
{
	if (!greenLight->link()) {
		return;
	}
	Logger->appendText(trUtf8("перелей из B в C"), trUtf8("перелей из B в C"), "OK");
	VodoleyObj->MoveFromTo(1, 2);
}

void VodoleyPult::BOutS()
{
	if (!greenLight->link()) {
		return;
	}
	Logger->appendText(trUtf8("вылей B"), trUtf8("вылей B"), "OK");
	VodoleyObj->MoveFromTo(1, 3);
}

void VodoleyPult::COutS()
{
	if (!greenLight->link()) {
		return;
	}
	if (VodoleyObj->Csize() == 0) {
		Logger->appendText(trUtf8("вылей C"), trUtf8("вылей C"), trUtf8("Отказ"));
		return;
	}
	Logger->appendText(trUtf8("вылей C"), trUtf8("вылей C"), "OK");
	VodoleyObj->MoveFromTo(2, 3);
}

void VodoleyPult::AOutS()
{
	if (!greenLight->link()) {
		return;
	}

	Logger->appendText(trUtf8("вылей A"), trUtf8("вылей A"), "OK");
	VodoleyObj->MoveFromTo(0, 3);

}

void VodoleyPult::AtoCS()
{
	if (!greenLight->link()) {
		return;
	}

	Logger->appendText(trUtf8("перелей из A в C"), trUtf8("перелей из A в C"), "OK");
	VodoleyObj->MoveFromTo(0, 2);
}

void VodoleyPult::FillAs()
{
	if (!greenLight->link()) {
		return;
	}

	Logger->appendText(trUtf8("наполни A"), trUtf8("наполни А"), "OK");
	VodoleyObj->FillA();
}

void VodoleyPult::FillBs()
{
	if (!greenLight->link()) {
		return;
	}

	Logger->appendText(trUtf8("наполни B"), trUtf8("наполни B"), "OK");
	VodoleyObj->FillB();
}

void VodoleyPult::FillCs()
{
	if (!greenLight->link()) {
		return;
	}
	if (VodoleyObj->Csize() == 0) {
		Logger->appendText(trUtf8("наполни C"), trUtf8("наполни C"), trUtf8("Отказ"));
		return;
	}
	Logger->appendText(trUtf8("наполни C"), trUtf8("наполни C"), "OK");
	VodoleyObj->FillC();
}

void VodoleyPult::TempS()
{
	if (!greenLight->link()) {
		return;
	}

	Logger->appendText(trUtf8("перелей из B в A"), trUtf8("перелей из B в A"), "OK");
	VodoleyObj->MoveFromTo(1, 0);
}

void VodoleyPult::AtoBS()
{
	if (!greenLight->link()) {
		return;
	}

	Logger->appendText(trUtf8("перелей из A в B"), trUtf8("перелей из A в B"), "OK");
	VodoleyObj->MoveFromTo(0, 1);
}



void VodoleyPult::CtoAS()
{
	if (!greenLight->link()) {
		return;
	}
	if (VodoleyObj->Csize() == 0) {
		Logger->appendText(trUtf8("перелей из C в A"), trUtf8("перелей из C в A"), trUtf8("Отказ"));
		return;
	}
	Logger->appendText(trUtf8("перелей из C в A"), trUtf8("перелей из C в A"), "OK");
	VodoleyObj->MoveFromTo(2, 0);
}


void VodoleyPult::CtoBS()
{
	if (!greenLight->link()) {
		return;
	}
	if (VodoleyObj->Csize() == 0) {
		Logger->appendText(trUtf8("перелей из C в B"), trUtf8("перелей из C в B"), trUtf8("Отказ"));
		return;
	}
	Logger->appendText(trUtf8("перелей из C в B"), trUtf8("перелей из C в B"), "OK");
	VodoleyObj->MoveFromTo(2, 1);
}


void VodoleyPult::resetVodoley()
{
	VodoleyObj->reset();
}

void VodoleyPult::newClient(QString message)
{
	label->setText(QString::fromUtf8("Подключился ") + message);
	toKumir->setEnabled(true);
}

void VodoleyPult::clientDisconnect()
{
	label->setText(QString::fromUtf8("Клиент отключился"));
	LinkOK();
}


void VodoleyPult::logToKumir()
{
	Logger->CopyLog();
}


void VodoleyPult::lockCButtons()
{
	CtoB->setEnabled(false);
	CtoA->setEnabled(false);
	AtoC->setEnabled(false);
	BtoC->setEnabled(false);
	cFill->setEnabled(false);
	Coutb->setEnabled(false);
}

void VodoleyPult::UnLockCButtons()
{
	CtoB->setEnabled(true);
	CtoA->setEnabled(true);
	AtoC->setEnabled(true);
	BtoC->setEnabled(true);
	cFill->setEnabled(true);
	Coutb->setEnabled(true);
}

void VodoleyPult::paintEvent(QPaintEvent *event)
{
	QPainter p(this);
	p.save();
	p.setPen(Qt::NoPen);
	p.setBrush(QColor("#32BAC3"));
	p.drawRect(0, 0, width(), height());
	p.restore();
	QWidget::paintEvent(event);
}
