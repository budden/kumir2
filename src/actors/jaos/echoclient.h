/****************************************************************************
****************************************************************************/
#ifndef ECHOCLIENT_H
#define ECHOCLIENT_H

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <QtNetwork>
#include <QTcpSocket>
#include <QtCore/QCoreApplication>

class ContainerThread : public QThread {

Q_OBJECT

public: 

QCoreApplication *app;
explicit ContainerThread(bool debug, QObject *parent, QCoreApplication *inApp);

void run() override;

Q_SIGNALS:
    void onEventLoopExitingg();

};


#endif // ECHOCLIENT_H
