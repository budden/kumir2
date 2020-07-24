#include "otimer.h"
#include <QDebug>
#include <QPainter>
#include <QPen>
#include <QMouseEvent>

const double DegreesPerMinute = 7.0;

OvenTimer::OvenTimer(QWidget *parent) : QWidget(parent)
{
	gradValue = 45;
	QFont font;
	font.setPointSize(8);
	setFont(font);
}

void OvenTimer::setDuration(int secs)
{
	gradValue = gradValue + secs;
	if (gradValue > 360) {
		gradValue = gradValue - 360;
	}
	if (gradValue < 0) {
		gradValue = 360 - gradValue;
	}
	emit angChange(gradValue);
	qDebug() << "Set " << secs;
}

int OvenTimer::duration() const
{
	return gradValue;
}

void OvenTimer::setValue(int value)
{
	gradValue = value;
	update();
}

void OvenTimer::mousePressEvent(QMouseEvent *event)
{
	Q_UNUSED(event);
	mouseFlag = true;
	QPointF point = event->pos() - rect().center();
	old_mouse_pos = point;
	qDebug() << "Mouse pos" << point;
	update();
}

void OvenTimer:: mouseMoveEvent(QMouseEvent *event)
{
	Q_UNUSED(event);
	if (!mouseFlag) {
		return;
	}
	QPointF point = event->pos() - rect().center();
	QPointF delta = old_mouse_pos - point;
	qDebug() << "Mouse Delta" << old_mouse_pos - point << " x coord" << point.x();
	if (point.x() > 0) {
		setDuration(-delta.y());
	} else {
		setDuration(delta.y());
	}

	old_mouse_pos = point;
	update();
}

void OvenTimer::mouseReleaseEvent(QMouseEvent *event)
{
	Q_UNUSED(event);
	mouseFlag = false;
}

void OvenTimer::paintEvent(QPaintEvent * /* event */)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);

	int side = qMin(width(), height());

	painter.setViewport((width() - side) / 2, (height() - side) / 2,
		side, side);
	painter.setWindow(-50, -50, 100, 100);

	draw(&painter);
}

void OvenTimer::draw(QPainter *painter)
{
	static const int triangle[3][2] = {
		{-2, -49}, {+2, -49}, {0, -47}
	};
	QPen thickPen(palette().foreground(), 1.5);
	QPen thinPen(palette().foreground(), 0.5);
	QColor niceBlue(200, 180, 130);
	QColor sand(220, 190, 150);
	QColor sandLight(244, 229, 111);
	painter->setPen(thinPen);
	painter->setBrush(palette().foreground());
	painter->drawPolygon(QPolygon(3, &triangle[0][0]));
	QConicalGradient coneGradient(0, 0, -90.0);
	coneGradient.setColorAt(0.0, sand);
	coneGradient.setColorAt(0.2, niceBlue);
	coneGradient.setColorAt(0.5, Qt::white);
	coneGradient.setColorAt(1.0, sand);

	painter->setBrush(coneGradient);
	painter->drawEllipse(-46, -46, 92, 92);
	QRadialGradient haloGradient(0, 0, 20, 0, 0);
	haloGradient.setColorAt(0.0, sandLight);
	haloGradient.setColorAt(0.8, sand);
	haloGradient.setColorAt(0.9, Qt::white);
	haloGradient.setColorAt(1.0, Qt::black);

	painter->setPen(Qt::NoPen);
	painter->setBrush(haloGradient);
	painter->drawEllipse(-20, -20, 40, 40);
	QLinearGradient knobGradient(-7, -25, 7, -25);
	knobGradient.setColorAt(0.0, Qt::black);
	knobGradient.setColorAt(0.2, niceBlue);
	knobGradient.setColorAt(0.3, sandLight);
	knobGradient.setColorAt(0.8, Qt::white);
	knobGradient.setColorAt(1.0, Qt::black);

	painter->rotate(duration());
	qDebug() << "Duration " << duration();
	painter->setBrush(knobGradient);
	painter->setPen(thinPen);
	painter->drawRoundRect(-7, -25, 14, 50, 99, 49);

	for (int i = 0; i <= 359; ++i) {
		if (i % 60 == 0) {
			painter->setPen(thickPen);
			painter->drawLine(0, -41, 0, -44);
			painter->drawText(-15, -41, 30, 30,
				Qt::AlignHCenter | Qt::AlignTop,
				QString::number(i));
		} else {
			if (i % 5 == 0) {
				painter->setPen(thinPen);
				painter->drawLine(0, -42, 0, -44);
			};
		}
		painter->rotate(-DegreesPerMinute);
	}
}

