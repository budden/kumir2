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
#ifndef PULT_H
#define PULT_H

#include "ui_pult.h"

class QDir;
class linkLight;
class pultLogger;
class MainButton;
class KumKuznec;

class GrasshopperPult : public QWidget, public Ui::GrasshopperPult
{
	Q_OBJECT
public:
	GrasshopperPult(const QDir &dir, QWidget *parent = 0, Qt::WindowFlags fl = 0);
	~GrasshopperPult() {};

	bool getLibMode() const { return libMode; }

	void AutoClose() { autoClose = true; }

public slots:
	void noLink();
	void LinkOK();

	void newClient(QString);
	void clientDisconnect();

	void Left();
	void Right();
	void ColorUnColor();

	void resetKuznec();
	void showMessage(QString message)
	{
		label->setText(message);
	}
	void logToKumir();
	void setStepSizes(int Fwd, int Back)
	{
		FwdNumber->display(Fwd);
		BackNumber->display(Back);
	}

signals:
	void sendText(QString text);

protected:
	virtual void closeEvent(QCloseEvent *event);

public: // eliminate this section
	KumKuznec *kuznecObj;

private:
	bool libMode;
	bool link;
	bool autoClose;
	pultLogger *Logger;
	linkLight *greenLight;
	MainButton *turnLeft, *turnRight, *recolorB, *askStena, *askFree;
};
#endif
