#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDir>
#include <QFile>

class MyServer: public QTcpServer{
    Q_OBJECT
public:
    MyServer();
    ~MyServer();
    QTcpSocket * socket;
    QByteArray Data;
    QString path_to_Download;

public slots:
    void StartServer();
    void incomingConnection(int socketDeskriptor);
    void sockReady();
    void sockDisc();
};


#endif // MYSERVER_H
