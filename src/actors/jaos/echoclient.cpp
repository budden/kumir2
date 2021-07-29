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

// https://stackoverflow.com/a/60192923
void ContainerThread::run()  {
    qDebug() << "entered ContainerThread::run";
    // container->startWork();
    QEventLoop eventLoop;
    QTcpSocket *socket = new QTcpSocket(&eventLoop);
    connect(socket, &QTcpSocket::readyRead, &eventLoop, [socket]
    {
        char in_data[1024];
        qDebug() << "entered readyToRead";
        if (socket->canReadLine()) {
            socket->readLine(in_data,sizeof(in_data));
        qDebug() << "onReadRead: readLine() got " << in_data; 
        socket->close();
        }
    });

    socket->connect(socket, &QAbstractSocket::connected, &eventLoop, [socket]{
        qint64 bytesWrittenNow = socket->write(QByteArray("1:17"));
        // Q_ASSERT(tcpClient.flush()); // пусть хоть упадёт, не знаю, как быть пока что.
        qDebug() << "Leaving startTransfer, bytes written to the buffer = " << bytesWrittenNow;        
    });

    // Quit the loop (and thread) if the socket it disconnected. You could also try
    // reconnecting
    socket->connect(socket, &QTcpSocket::disconnected, &eventLoop, [&eventLoop]
    {
        qDebug() << "QTcpSocket::disconnected signaled";
        eventLoop.quit();
    });

    socket->connectToHost(QHostAddress::LocalHost, 8967);

    eventLoop.exec();

    delete socket;

    qDebug() << "Thread object becomes an orphan, delete it please!";
    // app->quit();

}


