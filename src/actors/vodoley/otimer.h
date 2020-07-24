#ifndef OTIMER_H
#define OTIMER_H

#include <QWidget>
#include <QPoint>

class QPainter;
class QPaintEvent;
class QMouseEvent;

class OvenTimer : public QWidget
{
	Q_OBJECT

public:
	OvenTimer(QWidget *parent = 0);

	void setDuration(int secs);
	int duration() const;
	void draw(QPainter *painter);

signals:
	void angChange(int value);

public slots:
	void setValue(int value);

protected:
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

private:
	bool mouseFlag;
	QPointF old_mouse_pos;
	int gradValue;
	int oldValue;
};

#endif

