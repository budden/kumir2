/****************************************************************************
**
****************************************************************************/
#include "echoclient.h"
#include <QtCore/QDebug>

#include <QtNetwork>
#include <QAbstractSocket>
#include <QtGlobal>
#include <QObject>
#include <QtCore/QCoreApplication>

static const int PayloadSize = 256;

QT_USE_NAMESPACE

ContainerThread::ContainerThread(bool debug, QObject *parent, HackConnectEventCallback inEventConnector, QObject *inPlugin) : QThread (parent) {
    Q_UNUSED(debug);
    plugin = inPlugin;
    eventConnector = inEventConnector; 
    qDebug() << "entered ContainerThread::ContainerThread";
}

QJakClientEventLoop::QJakClientEventLoop(QObject *parent) : QEventLoop(parent) {
    connect(&socket, &QTcpSocket::readyRead, this,   
        &QJakClientEventLoop::onSocketReadyRead);

    connect(&socket, &QAbstractSocket::connected, this, 
        &QJakClientEventLoop::onSocketConnected) ;

    connect(&socket, &QTcpSocket::disconnected, this, 
        &QJakClientEventLoop::onSocketDisconnected);

    qDebug() << "create QJakClientEventLoop and bound it with the socket";

};


/* public slot */ void QJakClientEventLoop::onSocketReadyRead() {
    {
        char in_data[1024];
        qDebug() << "entered readyToRead";
        if (socket.canReadLine()) {
            socket.readLine(in_data,sizeof(in_data));
        qDebug() << "onReadyRead: readLine() got " << in_data; 
        //socket.close();
        emit GotReplyFromServer(QString::fromUtf8(in_data).toInt());
        }
    }
}

/* public slot */ void QJakClientEventLoop::sendCallToServer(const int function_number, const int arg) {
    qint64 bytesWrittenNow = socket.write(QString("%d:%d").arg(function_number).arg(arg).toUtf8());
    // Q_ASSERT(tcpClient.flush()); // пусть хоть упадёт, не знаю, как быть пока что.
    qDebug() << "Leaving startTransfer, bytes written to the buffer = " << bytesWrittenNow;        
}

/* public slot */ void QJakClientEventLoop::onSocketConnected() {
        qDebug() << "QJakClientEventLoop::onSocketConnected ";     
        emit Connected();
    }


/* public slot */ void QJakClientEventLoop::onSocketDisconnected() {
        qDebug() << "QTcpSocket::disconnected signaled";
        quit();    
}

void ContainerThread::startConnecting(int port) {
    eventLoop->socket.connectToHost(QHostAddress::LocalHost, port);
}

void ContainerThread::startDisconnecting() {
    qDebug() << "entered ContainerThread::startDisconnecting";
    eventLoop->socket.disconnect();
}

void ContainerThread::PleaseBindMyEvents() {
    (*eventConnector)(this,plugin);
}

// https://stackoverflow.com/a/60192923
void ContainerThread::run()  {
    qDebug() << "entered ContainerThread::run";
    // container->startWork();
    eventLoop = new QJakClientEventLoop(nullptr) ;
    qDebug() << "created event loop";

    PleaseBindMyEvents(); // а здесь надо как-то дождаться результата!!!
    msleep(500);

    qDebug() << "all signals should have been connected here. RACE CONDITION!";
    startConnecting(8967);
    qDebug() << "returned from startConnecting";
    eventLoop->exec();
    emit eventLoopDonee();

    //app->quit();

}


