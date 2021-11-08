#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDir>
#include <fstream>
#include <iostream>
using namespace std;

class MyServer: public QTcpServer{
    Q_OBJECT
public:
    MyServer();
    ~MyServer();
    QTcpSocket * socket;
    QByteArray Data;

public slots:
    void StartServer();
    void incomingConnection(int socketDeskriptor);
    void sockReady();
    void sockDisc();
};


#endif // MYSERVER_H
