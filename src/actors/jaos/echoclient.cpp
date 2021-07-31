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

ContainerThread::ContainerThread(bool debug, QObject *parent, QCoreApplication *inApp) : QThread (parent) {
    Q_UNUSED(debug);
    app = inApp;
    qDebug() << "entered ContainerThread::ContainerThread";

}

QJakClientEventLoop::QJakClientEventLoop(QObject *parent) : QEventLoop(parent) {
    connect(&socket, &QTcpSocket::readyRead, this,   
        &QJakClientEventLoop::onSocketReadyRead);

    connect(&socket, &QAbstractSocket::connected, this, 
        &QJakClientEventLoop::onSocketConnected) ;

    connect(&socket, &QTcpSocket::disconnected, this, 
        &QJakClientEventLoop::onSocketDisconnected);

};


void QJakClientEventLoop::onSocketReadyRead() {
    {
        char in_data[1024];
        qDebug() << "entered readyToRead";
        if (socket.canReadLine()) {
            socket.readLine(in_data,sizeof(in_data));
        qDebug() << "onReadRead: readLine() got " << in_data; 
        socket.close();
        }
    }
}

void QJakClientEventLoop::onSocketConnected() {
        emit Connected();
        qint64 bytesWrittenNow = socket.write(QByteArray("1:17"));
        // Q_ASSERT(tcpClient.flush()); // пусть хоть упадёт, не знаю, как быть пока что.
        qDebug() << "Leaving startTransfer, bytes written to the buffer = " << bytesWrittenNow;        

    }


void QJakClientEventLoop::onSocketDisconnected() {
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



// https://stackoverflow.com/a/60192923
void ContainerThread::run()  {
    qDebug() << "entered ContainerThread::run";
    // container->startWork();
    eventLoop = new QJakClientEventLoop(nullptr) ;
    qDebug() << "created event loop";

    connect(eventLoop,&QJakClientEventLoop::Connected,this,&ContainerThread::onConnected);
    qDebug() << "connected event";

    startConnecting(8967);
    qDebug() << "returned from startConnecting";
    eventLoop->exec();

    app->quit();

}


