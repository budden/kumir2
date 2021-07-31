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

class ContainerThread : public QThread {

Q_OBJECT

public: 

explicit ContainerThread(bool debug, QObject *parent);


QJakClientEventLoop *eventLoop;


void run() override;

Q_SIGNALS:
    void onEventLoopExitingg();
    void Connected();
    void SendCallToServer(const int function_number, const int arg);
    void GotReplyFromServer(const int result);

public slots:
    void startConnecting(int port);
    void onConnected() {
        qDebug() << "ContainerThread::onConnected";
        emit Connected();
    }
    void startDisconnecting();
    void onSendCallToServer(const int function_number, const int arg) {
        emit SendCallToServer(function_number, arg);
    }
    void onGotReplyFromServer(const int result) {
        emit GotReplyFromServer(result);
    }


};


#endif // ECHOCLIENT_H
