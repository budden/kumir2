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

#include "ui_pult.h"

class Vodoley;
class pultLogger;
class linkLight;
class MainButton;


class VodoleyPult : public QWidget, public Ui::VodoleyPult
{
	Q_OBJECT
public:
	/**
	 * Конструктор
	 * @param parent ссыка на объект-владелец
	 * @param fl флаги окна
	 */
	VodoleyPult(QWidget *parent = 0, Qt::WindowFlags fl = 0);
	~VodoleyPult() {};

	QSize minimumSizeHint() const { return QSize(250, 450); }
	bool Link() const { return link; }
	pultLogger *pltLogger() { return Logger; }
	void AutoClose() { autoClose = true; }

public slots:
	void noLink();
	void LinkOK();

	void newClient(QString);
	void clientDisconnect();

	void Up();

	void AOutS();
	void BOutS();
	void COutS();

	void TempS();

	void AtoBS();
	void AtoCS();
	void CtoBS();
	void CtoAS();

	void resetVodoley();
	void showMessage(QString message) { label->setText(message); }
	void logToKumir();

	void FillAs();
	void FillBs();
	void FillCs();

	void lockCButtons();
	void UnLockCButtons();

signals:
	void Clean();

protected:
	virtual void paintEvent(QPaintEvent *);

private:
	bool link;
	bool autoClose;
	linkLight *greenLight;
	MainButton *BtoC, *buttBack, *AtoC, *turnRight;
	MainButton *Coutb, *askFree, *AtoB, *buttTemp;
	MainButton *aFill, *bFill, *cFill, *CtoB, *CtoA;
	pultLogger *Logger;

public:
	Vodoley *VodoleyObj;

};

