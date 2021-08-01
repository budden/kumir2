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

ContainerThread::ContainerThread(bool debug, QObject *parent) : QThread (parent) {
    Q_UNUSED(debug);
    qDebug() << "done ContainerThread::ContainerThread";
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
        qint64 readLength;
        qDebug() << "entered readyToRead";
        if (socket.canReadLine()) {
            readLength = socket.readLine(in_data,sizeof(in_data));
            qDebug() << "onReadyRead: readLine() got " << readLength << " bytes: " << in_data; 
            lastCallResult = QString::fromUtf8(in_data).toInt();
            asyncCallStatusValue = acsvResultIsWaitingToBeConsumed;
        } else {
            qDebug() << "incomplete line";
        }
    }
}

/* public slot */ void QJakClientEventLoop::sendCallToServer(const int function_number, const int arg1) {
    asyncCallStatusValue = acsvRunning;
    qint64 bytesWrittenNow = socket.write(QString("%1:%2\n").arg(function_number).arg(arg1).toUtf8());
    Q_ASSERT(socket.flush());
    // Q_ASSERT(tcpClient.flush()); // пусть хоть упадёт, не знаю, как быть пока что.
    qDebug() << "Leaving startTransfer, bytes written to the buffer = " << bytesWrittenNow;        
}

/* public slot */ void QJakClientEventLoop::onSocketConnected() {
        qDebug() << "QJakClientEventLoop::onSocketConnected ";     
        connectionStatusValue = csvConnected;
        asyncCallStatusValue = acsvWaitingForACall;
        // emit Connected();
    }

/* public slot */void QJakClientEventLoop::startDisconnecting() {
    qDebug() << "entered QJakClientEventLoop::startDisconnecting";
    socket.disconnect();
}    


/* public slot */ void QJakClientEventLoop::onSocketDisconnected() {
        qDebug() << "QTcpSocket::disconnected signaled";
        connectionStatusValue = csvNoConnection; 
        asyncCallStatusValue = acsvDisconnected; 
        quit();    
}

/* public slot */ void QJakClientEventLoop::onResultConsumed() {
        qDebug() << "got a signal that the result is consumed";
        Q_ASSERT(asyncCallStatusValue == acsvResultIsWaitingToBeConsumed);
        asyncCallStatusValue = acsvWaitingForACall; 
}


void ContainerThread::startConnecting(int port) {
    eventLoop->socket.connectToHost(QHostAddress::LocalHost, port);
}

// https://stackoverflow.com/a/60192923
void ContainerThread::run()  {
    qDebug() << "entered ContainerThread::run";
    // container->startWork();
    eventLoop = new QJakClientEventLoop(nullptr) ;
    qDebug() << "created event loop";

    qDebug() << "all signals should have been connected here";
    startConnecting(8967);
    qDebug() << "returned from startConnecting";
    eventLoop->exec();
    emit eventLoopDonee();

    //app->quit();

}


