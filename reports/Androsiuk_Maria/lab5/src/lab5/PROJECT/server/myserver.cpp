#include "myserver.h"

MyServer::MyServer(){}
MyServer::~MyServer(){}

void MyServer::StartServer(){
    if(this->listen(QHostAddress::Any, 1919)) {
       qDebug() << "Listening";
    }
    else {
        qDebug() << "Not Listening";
    }
}

void MyServer::incomingConnection(int socketDeskriptor) {
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDeskriptor);
    connect(socket,SIGNAL(readyRead()), this, SLOT(sockReady()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));
    qDebug()<<socketDeskriptor<<"Client connected";
    qDebug()<<"Send client connect status - YES";
}

void MyServer::sockReady() {
    Data = socket->readAll();
    qDebug() << "Select from Client" << Data;


    if(!Data.isEmpty()) {

        QDir server_version(QDir::currentPath());
        QStringList filter;
        filter << "*.json";
        foreach(QFileInfo info, server_version.entryInfoList(filter)) {
            filter.clear();
            filter << info.absoluteFilePath();
        }
        qDebug() << filter;

        QFile file(filter.back());
        if (!file.open(QIODevice::ReadOnly))
            return;
        path_to_Download = file.readAll();
        if(QString(Data) == path_to_Download) {
            qDebug() << "Send to Client" << "Actuale";
            socket->write("Actuale");
        }

        else if(Data == "Yes") {
            Data.clear();
            QDir dir_server(QDir::currentPath());

            Data.append(dir_server.path()+' ' + "Colors.txt " + path_to_Download);

            qDebug() << "Send to Client" << Data;
            socket->write(Data);
        }

        else {
            qDebug() << "Send to Client" << "Need update";
            socket->write("Need update");
        }
        socket->waitForBytesWritten(100);
    }
}

void MyServer::sockDisc(){
    qDebug()<<"Disconnect";
    socket->deleteLater();
}
