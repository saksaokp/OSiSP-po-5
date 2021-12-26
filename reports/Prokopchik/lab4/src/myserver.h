#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include <QtCore>

class myserver: public QTcpServer
{
    Q_OBJECT
public:
    myserver();
    ~myserver();

    QTcpServer *tcpSever;
    QTcpSocket* socket;

public slots:
    void startServer();
    void incomingConnection(long long socketDescriptor);
    void sockReady();
    void sockDisc();
};

#endif // MYSERVER_H
