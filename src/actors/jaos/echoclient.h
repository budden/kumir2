/****************************************************************************
****************************************************************************/
#ifndef ECHOCLIENT_H
#define ECHOCLIENT_H

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <QtNetwork>
#include <QTcpSocket>

enum ConnectionStatusValue { csvNoConnection = 0, 
 csvConnecting = 1,
 csvConnectionError = 2,
 csvConnected = 3,
 csvDisconnecting = 4,
 csvDisconnectError = 5}; 

enum AsyncCallStatusValue {
 acsvRunning = 0,
 acsvDoneWithError = 1,
 acsvOk = 2,
 acsvDisconnected = 3
};


class QJakClientEventLoop : public QEventLoop {

Q_OBJECT
public:
    QTcpSocket socket;
    explicit QJakClientEventLoop(QObject *parent = nullptr);
    AsyncCallStatusValue asyncCallStatusValue = acsvDisconnected;
    ConnectionStatusValue connectionStatusValue = csvNoConnection;
    bool signalsFromPluginAreBoundP = false;
    int lastCallResult;

public slots:
    void onSocketReadyRead();
    void sendCallToServer(const int function_number, const int arg);
    void onSocketConnected();
    void onSocketDisconnected();
    void startDisconnecting();

};

typedef void (*HackConnectEventCallback)(QObject *thread, QObject *plugin);

class ContainerThread : public QThread {

Q_OBJECT

public: 

explicit ContainerThread(bool debug, QObject *parent);

HackConnectEventCallback eventConnector;

QJakClientEventLoop *eventLoop = nullptr;


void run() override;
void PleaseBindMyEvents();

Q_SIGNALS:

    void eventLoopDonee();
    //void Connected();
    //void SendCallToServer(const int function_number, const int arg);
    //void GotReplyFromServer(const int result);

public slots:
    void startConnecting(int port);
};


#endif // ECHOCLIENT_H
