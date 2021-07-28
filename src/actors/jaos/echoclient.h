/****************************************************************************
 * ** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
****************************************************************************/
#ifndef ECHOCLIENT_H
#define ECHOCLIENT_H

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <QtNetwork>
#include <QTcpSocket>

class EchoClient : public QObject
{
    Q_OBJECT

public:
    explicit EchoClient(int in_port_number, bool debug = false);

public slots:
    void start();
    void startTransfer();
    void updateClientProgress(qint64 numBytes);
    void displayError(QAbstractSocket::SocketError socketError);

public:
    int port_number;
    QTcpSocket tcpClient;
    QTcpSocket *tcpServerConnection = nullptr;
    int bytesToWrite = 0;
    int bytesWritten = 0;
    int bytesReceived = 0;

};

#endif // ECHOCLIENT_H
