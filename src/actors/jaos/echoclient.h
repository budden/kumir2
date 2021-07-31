/****************************************************************************
****************************************************************************/
#ifndef ECHOCLIENT_H
#define ECHOCLIENT_H

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <QtNetwork>
#include <QTcpSocket>

class QJakClientEventLoop : public QEventLoop {

Q_OBJECT
public:
    QTcpSocket socket;
    explicit QJakClientEventLoop(QObject *parent = nullptr);

public slots:
    void onSocketReadyRead();
    void sendCallToServer(const int function_number, const int arg);
    void onSocketConnected();
    void onSocketDisconnected();

Q_SIGNALS:
    void Connected();
    void GotReplyFromServer(const int result);

};

typedef void (*HackConnectEventCallback)(QObject *thread, QObject *plugin);

class ContainerThread : public QThread {

Q_OBJECT

public: 

explicit ContainerThread(bool debug, QObject *parent, HackConnectEventCallback inEventConnector, QObject *inPlugin);

HackConnectEventCallback eventConnector;
QObject *plugin; 

QJakClientEventLoop *eventLoop;


void run() override;
void PleaseBindMyEvents();

Q_SIGNALS:

    void eventLoopDonee();
    //void Connected();
    //void SendCallToServer(const int function_number, const int arg);
    //void GotReplyFromServer(const int result);

public slots:
    void startConnecting(int port);
    void startDisconnecting();


};


#endif // ECHOCLIENT_H
