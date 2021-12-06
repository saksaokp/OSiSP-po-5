#include "myserver.h"

MyServer::MyServer(){}
MyServer::~MyServer(){}

void MyServer::StartServer(){
    if(this->listen(QHostAddress::Any, 5555)) {
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

        else if(Data[0] == 'l') {
            QStringList client_data;
            client_data.append(QString(Data).split(" "));
            Data.clear();
            QDir dir_server(QDir::currentPath() + "/level");
            QStringList find_filter;

            Data.append(dir_server.path()+' ');

            bool ok = dir_server.exists();
            if (ok)
            {
                dir_server.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
                dir_server.setSorting(QDir::Name);
                QFileInfoList list = dir_server.entryInfoList();

                for (int i = 0; i < list.size(); ++i)
                {
                    QFileInfo fileInfo = list.at(i);
                    find_filter.append(fileInfo.fileName());
                }
            }
             QStringList sen_to_clien;
             for(int i = client_data.size(); i < find_filter.size(); i++) {
                 sen_to_clien.append(find_filter[i]);
             }
            foreach (const QString &str, sen_to_clien)
            {
                Data.append(str);
                if(&str != find_filter.last()) {
                    Data.append(" ");
                }
                else {
                    Data.append(" ");
                    Data.append(path_to_Download);

                }
            }
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
