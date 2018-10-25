#ifndef ROBOTVIEW_H
#define ROBOTVIEW_H

#include <QtGui>
#include <kumir2-libs/extensionsystem/kplugin.h>


namespace ActorRobot
{

class RobotModule;

enum RMode {
	NORMAL_MODE,
	NEDIT_MODE,
	TEMP_MODE,
	RAD_MODE,
	TEXT_MODE
};

enum CrashDir {
	NO_CRASH,
	UP_CRASH,
	DOWN_CRASH,
	LEFT_CRASH,
	RIGHT_CRASH
};

class EditLine: public QGraphicsObject
{
	Q_OBJECT;
public:
	EditLine(QGraphicsItem *parent = 0);
	QRectF boundingRect() const;

	bool isTemp() const { return istemp; }
	bool isRad() const { return !istemp; }
	void setValue(float value) { Value = value; }

	void setRad();
	void setTemp();

	void paint(
		QPainter *painter,
		const QStyleOptionGraphicsItem *option,
		QWidget *widget
	);

private:
	float Value;
	bool istemp;
	QDir resDir;

	QUrl iconPath;
	QImage rad;
	QPicture radiation, temp;
};

class  CFieldItem
{
public:
	CFieldItem();
	void setWalls(int wallByte);


	bool IsColored;
	float radiation;
	float temperature;
	QChar upChar;
	QChar downChar;
	bool mark;
	bool upWall;
	bool downWall;
	bool rightWall;
	bool leftWall;

};

class ConsoleField
{
public:
	ConsoleField(int w, int h);
	void createField(int w, int h);
	CFieldItem *getItem(int row, int col);
	CFieldItem *getCurItem(); //Item with robot
	bool goLeft();
	bool goRight();
	bool goUp();
	bool goDown();
	bool isUpWall();
	bool isDownWall();
	bool isLeftWall();
	bool isRightWall();

	int  Columns()
	{
		return rows.at(0).count();
	}
	int  Rows()
	{
		return rows.count();
	}
	int  robotRow()
	{
		return roboRow;
	}
	int  robotCol()
	{
		return roboCol;
	}
	int loadFromFile(QString filename);
	int consoleLoadFromDataStream(QIODevice *stream);

private:
	QList< QList<CFieldItem *> > rows;
	int roboRow;
	int roboCol;
};

class SimpleRobot: public QGraphicsObject
{
	Q_OBJECT;

public:
	SimpleRobot(QGraphicsItem *parent = 0);
	QRectF boundingRect() const;

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
		QWidget *widget);
	QGraphicsPolygonItem *RoboItem();
	void setCrash(uint dirct);
	void move(QPoint point);
	bool isMoving()
	{
		return moving;
	}
	void  setMoving(bool flag)
	{
		moving = flag;
	}
	//void show();
signals:
	void moved(QPointF point);
protected:
	void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
	void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
private:

	QGraphicsPolygonItem *Robot;
	bool ready, moving;
	uint crash;

};


class FieldItm: public QGraphicsWidget
{
	Q_OBJECT
public:

	FieldItm(QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
	~FieldItm();

	FieldItm *Copy();
	void cleanSelf();

	void setLeftsepItem(FieldItm *ItmLeft);

	void setRightsepItem(FieldItm *ItmRight);

	void setUpsepItem(FieldItm *ItmUp);

	void setDownsepItem(FieldItm *ItmDown);
	void removeDownsepItem();
	void removeLeftsepItem();
	void removeRightsepItem();
	void setWalls(int wallByte);

	int wallByte();
	void showCharFld(qreal upLeftCornerX, qreal upLeftCornerY, int field_size);
	void hideCharFld();
	void setUpLine(QGraphicsLineItem *Line, QPen pen);

	void showCharMark(qreal upLeftCornerX, qreal upLeftCornerY, int size);
	void showUpChar(qreal upLeftCornerX, qreal upLeftCornerY, int size);
	void showDownChar(qreal upLeftCornerX, qreal upLeftCornerY, int size);
	void showRTItm(qreal upLeftCornerX, qreal upLeftCornerY, int size, int mode);
	void hideRTItm();

	void showMark(qreal upLeftCornerX, qreal upLeftCornerY, int size);

	void setColorRect(QGraphicsRectItem *Rect, QColor color);
	void setDownLine(QGraphicsLineItem *Line, QPen pen);
	void setLeftLine(QGraphicsLineItem *Line, QPen pen);
	void setRightLine(QGraphicsLineItem *Line, QPen pen);
	bool hasUpWall();
	bool hasDownWall();

	bool hasLeftWall();
	bool hasRightWall();

	bool canUp();
	bool canDown();
	bool canLeft();
	bool canRight();
	bool hasUpSep();
	bool hasDownSep();

	bool hasLeftSep();
	bool hasRightSep();
	QGraphicsLineItem *UpWallLine() const;
	QGraphicsLineItem *DownWallLine() const;
	QGraphicsLineItem *LeftWallLine() const ;
	QGraphicsLineItem *RightWallLine() const;
	bool isColored() const;

	void removeUpWall();

	void setUpWall(QGraphicsLineItem *Line, QPen pen);
	void setDownWall(QGraphicsLineItem *Line, QPen pen);
	void removeDownWall();

	void removeLeftWall();
	void removeRightWall();


	void setLeftWall(QGraphicsLineItem *Line, QPen pen);
	void setRightWall(QGraphicsLineItem *Line, QPen pen);

	void removeColor();

	void removeMark();

	void removeUpChar();

	void removeDownChar();
	bool emptyCell();
	void setScene(QGraphicsScene *scene);
	void wbWalls();
	void colorWalls();
	void setTextColor();
public:
	bool IsColored;
	float radiation;
	float temperature;
	QChar upChar;
	QChar downChar;
	bool mark;
	bool upWall;
	bool downWall;
	bool rightWall;
	bool leftWall;
private:

	QFont font;


	QPen wallPen;
	QGraphicsScene *Scene;
	QGraphicsLineItem *upWallLine;
	QGraphicsLineItem *downWallLine;
	QGraphicsLineItem *leftWallLine;
	QGraphicsLineItem *rightWallLine;
	QGraphicsRectItem *ColorRect;

	QGraphicsTextItem *upCharItm;
	QGraphicsTextItem *downCharItm;
	QGraphicsTextItem *markItm;
	EditLine *radItm;
	EditLine *tempItm;
	QGraphicsRectItem *upCharFld;
	QGraphicsRectItem *downCharFld;

	QColor TextColor;

	FieldItm *sepItmUp;
	FieldItm *sepItmDown;
	FieldItm *sepItmLeft;
	FieldItm *sepItmRight;
	QFont charFnt;
	ExtensionSystem::SettingsPtr sett;
};

class RoboField: public QGraphicsScene
{
	Q_OBJECT
public:
	RoboField(QWidget *parent, RobotModule *actor);
	RoboField *Clone() const ;
	~RoboField();

public:
	void drawField(uint cellSize);//TODO Document
	void destroyField();
	void setTextEditMode(bool flag);
	// void setRadEditMode(bool flag);
	void redrawEditFields();
	void redrawRTFields();
	void destroyRobot();


	inline int rows() const
	{
		return Items.count();
	}

	inline int columns() const
	{
		return Items.isEmpty() ? 0 : Items.last().size();
	}
	void drawNet();
	qreal m_height() const;
	qreal m_width() const;
	void setItem(FieldItm *item, uint str, uint stlb);
	void destroyNet();
	void destroyScene();
	void createField(int shirina, int visota);
	FieldItm *getFieldItem(int str, int stlb) const;
	void debug() const;
	void setColorFromSett();
	int loadFromFile(const QString &fileName);
	int loadFromDataStream(QIODevice *l_File);
	int saveToFile(QString fileName);
	void createRobot();
	void UpdateColors();
	void showCursorUp(int row, int col);
	void showCursorDown(int row, int col);

	/**
	 * –£–¥–∞–ª—è–µ—Ç / —Å—Ç–∞–≤–∏—Ç –≤–µ—Ä—Ö–Ω—é—é —Å—Ç–µ–Ω—É
	 * @param row –†—è–¥
	 * @param col —Å—Ç–æ–ª–±–µ—Ü
	 *
	 */
	void reverseUpWall(int row, int col);

	/**
	 * –£–¥–∞–ª—è–µ—Ç / —Å—Ç–∞–≤–∏—Ç –Ω–∏–∂–Ω—é—é —Å—Ç–µ–Ω—É
	 * @param row –†—è–¥
	 * @param col —Å—Ç–æ–ª–±–µ—Ü
	 *
	 */
	void reverseDownWall(int row, int col);
	void reverseLeftWall(int row, int col);
	void reverseRightWall(int row, int col);



	void showUpWall(int row, int col);

	/**
	 * –£–¥–∞–ª—è–µ—Ç / —Å—Ç–∞–≤–∏—Ç –Ω–∏–∂–Ω—é—é —Å—Ç–µ–Ω—É
	 * @param row –†—è–¥
	 * @param col —Å—Ç–æ–ª–±–µ—Ü
	 *
	 */
	void showDownWall(int row, int col);
	void showLeftWall(int row, int col);
	void showRightWall(int row, int col);


	void reverseColor(int row, int col);
	void reverseColorCurrent();

	void reverseMark(int row, int col);

	bool isEditMode() const
	{
		return mode > 0;
	}

	inline QList<QList<FieldItm * > > FieldItems()
	{
		return Items;
	}
	void setFieldItems(QList<QList<FieldItm * > > FieldItems);

	QPointF roboPosF() const
	{
		if (robot) {
			return robot->scenePos() ;
		}
		return QPointF(0, 0);
	};
	bool stepUp();
	bool stepDown();
	bool stepLeft();
	bool stepRight();
	void editField();
	void setMode(int Mode);//swich mode (show/hide controls etc.)
	void setModeFlag(int Mode)
	{
		mode = Mode;
	}

	inline FieldItm *currentCell()const
	{
		return getFieldItem(robo_y, robo_x);
	}
	inline FieldItm *cellAt(int x, int y)const
	{
		return getFieldItem(x, y);
	}

	inline void setMarkMode(bool isColor)
	{
		markMode = isColor;
	}

	inline bool WasEdit() const
	{
		return wasEdit;
	}

	void setRoboPos(int roboX, int roboY);
	inline int robotX() const
	{
		return robo_x;
	}
	inline int robotY() const
	{
		return robo_y;
	}


	inline void dropWasEdit()
	{
		wasEdit = false;
	}
	SimpleRobot *robot;
	void wbMode();
	void colorMode();
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
	public

slots:
	void roboMoved(QPointF pos);
	void cellDialogOk();
	void timerTic();
	void addRow();
	void remRow();
	void remCol();
	void addCol();
signals:
	void MousePress(qreal x, qreal y, bool Flag);
	// void was_edit();



private:

	void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);

	void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
	void keyPressEvent(QKeyEvent *keyEvent);
	void showButtons(bool yes);
	void createResizeButtons();
	QTimer *timer;
	QList<QList<FieldItm * > > Items;
	QList<QGraphicsLineItem *> setka;
	//QGraphicsView * scena;
	bool markMode, wasEdit;
	QColor LineColor, EditLineColor, WallColor, EditColor, NormalColor, Color;
	uint fieldSize;
	uint robo_x, robo_y;
	QWidget *Parent;
	QPen BortLine, StLine, showLine, WallLine;
	// CellDialog* cellDialog;
	bool WasEditFlag;
	//TOOLS
	QPoint upLeftCorner(int str, int stlb);
	bool pressed;
	// RobotModule *m_robot;
	ExtensionSystem::SettingsPtr sett;
	QRectF  oldRect;
	qreal perssX, pressY;
	QGraphicsLineItem *showWall, *keyCursor;
	QPair<int, int> old_cell, clickCell;
	bool pressD;
	QDoubleSpinBox *radSpinBox;
	QSpinBox *tempSpinBox;
	QGraphicsProxyWidget *wAddRow, *wAddCol, *wRemCol, *wRemRow;
	QToolButton *btnAddRow, *btnAddCol, *btnRemCol, *btnRemRow;
	int mode;
	RobotModule *Actor;

};


class RobotView: public QGraphicsView
{
	Q_OBJECT
public:
	RobotView(RoboField *roboField);
	void  FindRobot();
	void showButtons(bool flag);
	QSize   sizeHint() const;
	void setField(RoboField *field)
	{
		robotField = field;
	}
	void setWindowSize(const QSize newGeometry);
public slots:
	void handleDocked();
	void changeEditMode(bool state);
	void setDock(bool);
	void reloadSett(ExtensionSystem::SettingsPtr settings);
signals:
	void resizeRequest(const QSize &newGeometry);
protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);
	void showEvent(QShowEvent *event);
private:
	bool pressed, inDock, firstShow;
	int pressX, pressY;
	RoboField *robotField;
	QToolButton *textEditBtn;
	QToolButton *radEditBtn;
	QToolButton *tmpEditBtn;
	double c_scale;
	int CurCellSize;

};

} // ActorRobot

#endif // ROBOTVIEW_H
