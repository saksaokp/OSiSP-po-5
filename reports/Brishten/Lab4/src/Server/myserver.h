#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QDir>
#include <QtCore>

class myserver: public QTcpServer
{
    Q_OBJECT
public:
    myserver();
    ~myserver();

    QTcpServer *tcpSever;
    QTcpSocket* socket;
    QByteArray Data;

public slots:
    void startServer();
    void incomingConnection(int socketDescriptor);
    void sockReady();
    void sockDisc();
};

#endif // MYSERVER_H
