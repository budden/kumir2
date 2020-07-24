#ifndef VIAL_H
#define VIAL_H

#include <QGraphicsItem>
class QMutex;

class Vial: public QGraphicsItem
{

public:
	Vial(int x, int y, uint size, float lsize, QMutex *mutex);
	~Vial() {};

	QRectF boundingRect() const
	{
		qreal penWidth = 1;
		return QRectF(
			-10 - penWidth / 2, -10 - penWidth / 2,
			+20 + penWidth / 2, +20 + penWidth / 2
		);
	}

	void paint(
		QPainter *painter,
		const QStyleOptionGraphicsItem *option,
		QWidget *widget
	);

	void setGp(int gp);
	void setGpY(int gpy);

	void setCurFill(uint value) { curFil = value; }
	void setNeedFill(uint value) { needFill = value; }
	void setSize(uint value) { SizeInLiters = value; }
	void setLiterSize(float value) { literSize = value; }
	void setYoffset(float value) { offsetY = value; }

private:
	uint SizeInLiters;
	float literSize;
	uint curFil;
	int  needFill;
	int offsetX;
	int offsetY;
	int Gp, GpY;
	QMutex *M;

};

#endif
