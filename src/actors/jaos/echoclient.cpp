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
    connect(&tcpClient, &QIODevice::bytesWritten,
            this, &EchoClient::updateClientProgress);
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

void EchoClient::updateClientProgress(qint64 numBytes)
{
    // called when the TCP client has written some bytes
    bytesWritten += int(numBytes);

    // only write more if not finished and when the Qt write buffer is below a certain size.
    //if (bytesToWrite > 0 && tcpClient.bytesToWrite() <= 4 * PayloadSize)
    //    bytesToWrite -= tcpClient.write(QStringByteArray(qMin(bytesToWrite, PayloadSize), '@')
    //);

    qDebug() << "Written " << bytesWritten;

    tcpClient.close();
}

void EchoClient::startTransfer()
{
    // called when the TCP client connected to the loopback server
    qint64 bytesWrittenNow = tcpClient.write(QByteArray("1:1"));
    qDebug() << "Leaving startTransfer, bytes written = " << bytesWrittenNow;
    
}