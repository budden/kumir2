/****************************************************************************
**
****************************************************************************/
#include "echoclient.h"
#include <QtCore/QDebug>

#include <QtNetwork>
#include <QAbstractSocket>
#include <QtGlobal>
static const int PayloadSize = 256;

QT_USE_NAMESPACE

//! [constructor]
EchoClient::EchoClient(int in_port_number, bool m_debug) :
    QObject(nullptr)
{
    port_number = in_port_number;
    if (m_debug)
        qDebug() << "Creating dialog" ;
    connect(&tcpClient, &QAbstractSocket::connected, this, &EchoClient::startTransfer);
    connect(&tcpClient, &QIODevice::readyRead,
            this, &EchoClient::onReadyRead);
    connect(&tcpClient, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
            this, &EchoClient::displayError);
}
//! [constructor]

void EchoClient::start()
{

    bytesWritten = 0;
    bytesReceived = 0;
    qDebug() << "EchoClient::start : connecting to localhost:" << port_number ;

    tcpClient.connectToHost(QHostAddress::LocalHost, port_number);
}

void EchoClient::displayError(QAbstractSocket::SocketError socketError)
{
    if (socketError == QTcpSocket::RemoteHostClosedError)
        return;

    qDebug() << "Network error" << "The following error occurred: %1." <<  tcpClient.errorString();

    tcpClient.close();
}

void EchoClient::onReadyRead()
{ 
    char in_data[1024];
    qDebug() << "Entered onReadyRead";
    Q_ASSERT(tcpClient.bytesToWrite() == 0);
    if (tcpClient.canReadLine()) {
        tcpClient.readLine(in_data,sizeof(in_data));
        qDebug() << "onReadRead: readLine() got " << in_data; 
    }
}

void EchoClient::startTransfer()
{
    // called when the TCP client connected to the loopback server
    qint64 bytesWrittenNow = tcpClient.write(QByteArray("1:3"));
    bool flush_result = tcpClient.flush();
    Q_ASSERT(flush_result);
    qDebug() << "Leaving startTransfer, bytes written = " << bytesWrittenNow;
    
}