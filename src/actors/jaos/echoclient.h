/****************************************************************************
****************************************************************************/
#ifndef ECHOCLIENT_H
#define ECHOCLIENT_H

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <QtNetwork>
#include <QTcpSocket>
#include <QtCore/QCoreApplication>


class QJakClientEventLoop : public QEventLoop {

Q_OBJECT
public:
    QTcpSocket socket;
    explicit QJakClientEventLoop(QObject *parent = nullptr);

public slots:
    void onSocketReadyRead();
    void onSocketConnected();
    void onSocketDisconnected();

};

class ContainerThread : public QThread {

Q_OBJECT

public: 

explicit ContainerThread(bool debug, QObject *parent, QCoreApplication *inApp);


QCoreApplication *app;
QJakClientEventLoop *eventLoop;


void run() override;

Q_SIGNALS:
    void onEventLoopExitingg();

public slots:
    void startConnecting(int port);
    void startDisconnecting();


};


#endif // ECHOCLIENT_H
