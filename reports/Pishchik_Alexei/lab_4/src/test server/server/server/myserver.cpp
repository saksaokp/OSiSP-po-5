#include "myserver.h"
#include <QFile>
#include <QDate>

MyServer::MyServer(){}
MyServer::~MyServer(){}

void MyServer::StartServer(){
    if(this->listen(QHostAddress::Any, 5555)){
       qDebug() << "Listening";
    }
    else {
        qDebug() << "Not Listening";
    }
}

void MyServer::incomingConnection(int socketDeskriptor){
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
    QStringList client_data;
    client_data.append(QString(Data).split(" "));

    if(!Data.isEmpty()) {
        string result_client;
        ifstream f;
        f.open("C:\\Users\\Toketsu\\Desktop\\QT_3 _lab\\lab1\\debug\\client.json");
        getline(f, result_client);
        f.close();
        QString data_client = QString::fromStdString(result_client);

        string json_server;
        ifstream f1;
        f1.open("C:\\Users\\Toketsu\\Desktop\\test server\\server\\server\\debug\\server.json");
        getline(f1, json_server);
        f1.close();
        QString data = QString::fromStdString(json_server);
        if(data_client == data) {
            qDebug() << "Send to Client" << "Actuale";
            socket->write("Actuale");
        }
        else {
            QByteArray wr;
            QDir dir_server(QDir::currentPath());
            QStringList find_filter;
            dir_server.cd("plugins");
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
                wr.append(str);
                if(&str != find_filter.last()) {
                    wr.append(" ");
                }
            }

            qDebug() << "Send to Client" << wr;

            string result;
            ifstream f1;
            f1.open("C:\\Users\\Toketsu\\Desktop\\test server\\server\\server\\server.json");
            getline(f1, result);
            f1.close();
            QString data = QString::fromStdString(result);

            string result_client;
            ifstream f;
            f.open("C:\\Users\\Toketsu\\Desktop\\QT_3 _lab\\lab1\\debug\\client.json");
            getline(f, result_client);
            f.close();
            QString data_client = QString::fromStdString(result_client);
            data_client = data;

            ofstream write_json_clien;
            write_json_clien.open("C:\\Users\\Toketsu\\Desktop\\QT_3 _lab\\lab1\\debug\\client.json");
            write_json_clien << data_client.toStdString();
            write_json_clien.close();

            //create log
            ofstream write_log;
            write_log.open("C:/Users/Toketsu/Desktop/test server/server/server/debug/logs/log.txt");
            write_log << "Update to " + data_client.toStdString()<< " and modules: " << QString(wr).toStdString();
            write_log.close();

            socket->write(wr);
        }
        socket->waitForBytesWritten(100);
    }
}

void MyServer::sockDisc(){
    qDebug()<<"Disconnect";
    socket->deleteLater();
}
