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

#include "pult.h"
#include "kuznec.h"
#include "kumir2-libs/widgets/pultlogger.h"
#include <QtCore>

#define TEXT_STEP 14


linkLight::linkLight(QWidget *parent): QWidget(parent)
{
	posX = 1;
	posY = 1;
	onLine = true;
	text = trUtf8("СВЯЗЬ");
}

void linkLight::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	QRectF rectangle(posX, posY, 10.0, 10.0);

	QPen pen(Qt::green);  // creates a default pen

	QBrush brush(Qt::green);
	if (!onLine)
		brush.setColor(QColor(20, 60, 20));
	brush.setStyle(Qt::SolidPattern);
	painter.setPen(pen);
	painter.setBrush(brush);
	painter.drawEllipse(rectangle);

	brush.setColor(QColor(10, 10, 10));
	painter.setPen(QPen(QColor(10, 10, 10)));
	painter.setBrush(brush);
	QFont font("Arial");
	font.setBold(true);
	painter.setFont(font);
	int cur_pos = 0;
	for (int i = 0; i < text.length(); i++) {
		painter.drawText(posX, posY + TEXT_STEP * i + 26, QString(text[i]));
		cur_pos = posY + TEXT_STEP * i + 26;
	}
	QRectF rectangle2(posX, cur_pos + 7, 10, 10);
	brush.setColor(QColor(30, 0, 0));
	if (!onLine) {
		brush.setColor(QColor(250, 50, 50));
	}
	pen.setColor(Qt::red);

	brush.setStyle(Qt::SolidPattern);
	painter.setPen(pen);
	painter.setBrush(brush);
	painter.drawEllipse(rectangle2);
}

GrasshopperPult::GrasshopperPult(
	const QDir &resdir, QWidget *parent, Qt::WindowFlags fl
) : QWidget(parent, fl), Ui::GrasshopperPult()
{
	autoClose = false;
	setupUi(this);

	Logger = new pultLogger(resdir, this);
	Logger->setSizes(164, 150);
	Logger->Move(40, 5);
	greenLight = new linkLight(this);
	greenLight->move(15, 29);
	greenLight->resize(12, 104);

	LeftB->hide();
	turnLeft = new MainButton(resdir, this);
	turnLeft->setGeometry(LeftB->geometry());
	turnLeft->setText(" ");
	turnLeft->loadIcon(resdir.absoluteFilePath("160_55l.png"));

	turnRight = new MainButton(resdir, this);
	turnRight->setGeometry(RightB->geometry());
	turnRight->setText(" ");
	turnRight->loadIcon(resdir.absoluteFilePath("160_55r.png"));

	askStena = new MainButton(resdir, this);
	askStena->setCheckable(true);
	askStena->setText(trUtf8("  "));
	askStena->loadIcon(resdir.absoluteFilePath("stena.png"));
	askStena->setCheckable(true);
	askStena->hide();
	askFree = new MainButton(resdir, this);
	askFree->setCheckable(true);
	askFree->setText(trUtf8(" "));
	askFree->loadIcon(resdir.absoluteFilePath("svobodno.png"));
	askFree->setCheckable(true);
	askFree->hide();

	recolorB = new MainButton(resdir, this);
	recolorB->setGeometry(colorB->geometry());
	recolorB->setText(trUtf8("  "));
	recolorB->loadIcon(resdir.absoluteFilePath("recolor.png"));
	colorB->hide();

	QIcon toKumirIco(resdir.absoluteFilePath("kumir.png"));
	toKumir->setEnabled(true);
	toKumir->setIcon(toKumirIco);
	ClearLog->setIcon(QIcon(resdir.absoluteFilePath("clear.png")));

	connect(turnLeft, SIGNAL(clicked()), this, SLOT(Left()));
	connect(turnRight, SIGNAL(clicked()), this, SLOT(Right()));

	connect(ClearLog, SIGNAL(clicked()), Logger, SLOT(ClearLog()));
	connect(ClearLog, SIGNAL(clicked()), this, SLOT(resetKuznec()));

	connect(toKumir, SIGNAL(clicked()), Logger, SLOT(CopyLog()));
	connect(recolorB, SIGNAL(clicked()), this, SLOT(ColorUnColor()));
	setMinimumSize(254, 400);
	link = true;
}

void GrasshopperPult::noLink()
{
	link = false;
	greenLight->setLink(link);
	greenLight->repaint();
	qWarning("NoLINK");
	ClearLog->setEnabled(false);
	toKumir->setEnabled(false);
}

void GrasshopperPult::LinkOK()
{
	qDebug() << "LinkOK";
	link = true;
	greenLight->setLink(link);
	greenLight->repaint();
	ClearLog->setEnabled(true);
	toKumir->setEnabled(true);
}

void GrasshopperPult::Left()
{
	if (!greenLight->link())
		return;

	if (kuznecObj->canBack()) {
		Logger->appendText(
			QString::fromUtf8("назад ") +
				QString::number(BackNumber->intValue()),
			QString::fromUtf8("назад ") +
				QString::number(BackNumber->intValue()),
			"OK"
		);
		kuznecObj->MoveBack();
	} else {
		Logger->appendText(
			QString::fromUtf8("назад ") +
				QString::number(BackNumber->intValue()),
			QString::fromUtf8("назад ") +
				QString::number(BackNumber->intValue()),
			QString::fromUtf8("ОТКАЗ")
		);
	}
}

void GrasshopperPult::Right()
{
	if (!greenLight->link())
		return;

	if (kuznecObj->canFwd()) {
		Logger->appendText(
			QString::fromUtf8("вперед ") +
				QString::number(FwdNumber->intValue()),
			QString::fromUtf8("вперед ") +
				QString::number(FwdNumber->intValue()),
			"OK"
		);
		kuznecObj->MoveFwd();
	} else {
		Logger->appendText(
			QString::fromUtf8("вперед ") +
				QString::number(FwdNumber->intValue()),
			QString::fromUtf8("вперед ") +
				QString::number(FwdNumber->intValue()),
			QString::fromUtf8("ОТКАЗ")
		);
	}
}

void GrasshopperPult::resetKuznec()
{
	kuznecObj->Reset();
}

void GrasshopperPult::newClient(QString message)
{
	label->setText(QString::fromUtf8("Подключился ") + message);
	qDebug() << "Connected";
	toKumir->setEnabled(true);
}

void GrasshopperPult::clientDisconnect()
{
	label->setText(QString::fromUtf8("Клиент отключился"));
	qDebug() << "Disconect";
	LinkOK();
	toKumir->setEnabled(false);

}

void GrasshopperPult::logToKumir()
{
	emit sendText(Logger->log());
}

void GrasshopperPult::closeEvent(QCloseEvent *event)
{
	if (libMode || autoClose) {
		close();
		event->accept();
		return;
	}

	int ret = QMessageBox::warning(this,
		QString::fromUtf8("Кузнечик"),
		QString::fromUtf8("Закрыть исполнитель кузнечик?"),
		QMessageBox::Yes | QMessageBox::Default,
		QMessageBox::No,
		QMessageBox::Cancel | QMessageBox::Escape
	);
	if (ret == QMessageBox::Yes) {
		kuznecObj->AutoClose();
		kuznecObj->close();
		event->accept();
	} else {
		event->ignore();
	}
}

void GrasshopperPult::ColorUnColor()
{
	Logger->appendText(QString::fromUtf8("перекрасить"), QString::fromUtf8("перекрасить"), "OK");
	kuznecObj->ColorUncolor();
}

#if 0
void GrasshopperPult::paintEvent(QPaintEvent *event)
{
	QPainter p(this);
	p.setBrush(QColor("#7EB676"));
	p.drawRect(QRect(0, 0, width(), height()));
	p.end();
	event->accept();
}
#endif
