#include "vial.h"
#include <QMutex>
#include <QDebug>
#include <QPainter>

#define X_SIZE 30

void Vial::setGp(int gp)
{
	qDebug() << "Gp" << gp;
	Gp = gp;
	update();
}

void Vial::setGpY(int gpy)
{
	qDebug() << "GpY" << gpy;
	GpY = gpy;
	update();
}

Vial::Vial(int x, int y, uint size, float lsize, QMutex *mutex)
{
	SizeInLiters = size;
	literSize = lsize;
	offsetX = x + 5;
	offsetY = y;
	Gp = 23;
	GpY = 4;
	curFil = 1;
	needFill = -1;
	M = mutex;
}


void Vial::paint(
	QPainter *painter,
	const QStyleOptionGraphicsItem *option,
	QWidget *widget)
{

	Q_UNUSED(option);
	Q_UNUSED(widget);
	M->lock();
	QBrush black(Qt::black);
	float size = (literSize * SizeInLiters);
	QPointF points[4] = {
		QPointF(offsetX, offsetY + size - 3),
		QPointF(offsetX - 3, offsetY + size + 2),
		QPointF(offsetX + X_SIZE + 3, offsetY + size + 2),
		QPointF(offsetX + X_SIZE, offsetY + size - 3)
	};

	painter->setBrush(black);
	painter->drawConvexPolygon(points, 4);

	QLinearGradient glassGradient(offsetX, offsetY, offsetX + X_SIZE, offsetY + size);
	QColor niceBlue(142, 140 + 26, 180 + 25);
	QColor semiWhite(230, 230, 250);

	glassGradient.setColorAt(0.0, Qt::white);
	glassGradient.setColorAt(23 / 20, niceBlue);
	glassGradient.setColorAt(4 / 20, semiWhite);

	//Menzurka
	painter->setBrush(glassGradient);
	painter->drawRoundedRect(offsetX, offsetY - 5, X_SIZE, size + 5, 5, 5);
	//Birka
	QString text = QString::number(curFil);
	QPointF birka[5] = {
		QPointF(offsetX + X_SIZE + 3, offsetY + size - literSize * curFil),
		QPointF(offsetX + X_SIZE + 11, offsetY + size - literSize * curFil + 8),
		QPointF(offsetX + X_SIZE + 17 + text.length() * 10, offsetY + size - literSize * curFil + 8),
		QPointF(offsetX + X_SIZE + 17 + text.length() * 10, offsetY + size - literSize * curFil - 8),
		QPointF(offsetX + X_SIZE + 11, offsetY + size - literSize * curFil - 8)
	};
	painter->drawConvexPolygon(birka, 5);
	painter->drawText(offsetX + X_SIZE + 13, offsetY + size - literSize * curFil + 7, text); //Birka text
	QString sizeT = QString::number(SizeInLiters);
	painter->drawText(offsetX + X_SIZE / 2 - sizeT.length() * 3, offsetY + size + 20, sizeT);

	//Metki
	if (((uint)needFill > 0) && ((uint)needFill <= SizeInLiters)) {
		painter->setPen(QColor(20, 237, 17));
		painter->drawLine(offsetX + 1, offsetY + size - literSize * needFill, offsetX + X_SIZE / 3, offsetY + size - literSize * needFill);
		painter->setPen(QColor(150, 150, 150));
		painter->drawLine(offsetX + X_SIZE * 3 / 4, offsetY + size - literSize * SizeInLiters, offsetX + X_SIZE - 1, offsetY + size - literSize * SizeInLiters);
	};
	painter->setPen(QColor(0, 0, 0));

	//VODA
	if (curFil > 0) {
		QLinearGradient waterGradient(offsetX + 1, offsetY + size - literSize * curFil, offsetX + X_SIZE - 2, offsetY + size);
		QColor W1(78, 127, 248);
		QColor W2(18, 173, 253);
		qDebug() << "cur" << curFil << " need" << needFill;
		if (curFil == (uint)needFill) {
			qDebug() << "OK!!!!!!";
			W1.setRgb(250, 250, 35);
			W1.setRgb(210, 230, 10);
		};
		waterGradient.setColorAt(0.0, W1);
		if (curFil == (uint)needFill) {
			waterGradient.setColorAt(1, W2);
		} else {
			waterGradient.setColorAt(0.3, W2);
		}
		painter->setBrush(waterGradient);
		painter->setOpacity(0.5);
		painter->drawRoundedRect(
			offsetX, offsetY + size - literSize * curFil,
			X_SIZE, literSize * curFil,
			2, 2
		);
	}

	M->unlock();
}

