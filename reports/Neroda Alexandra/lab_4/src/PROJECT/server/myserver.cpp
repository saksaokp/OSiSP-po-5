#include "myserver.h"

MyServer::MyServer(){}
MyServer::~MyServer(){}

void MyServer::StartServer(){ //если он стартовал, то сервер готов к работе
    if(this->listen(QHostAddress::Any, 5555)) {
       qDebug() << "Listening";
    }
    else {
        qDebug() << "Not Listening";
    }
}

void MyServer::incomingConnection(int socketDeskriptor) { //инициализация подключаемого клиента
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDeskriptor);
    connect(socket,SIGNAL(readyRead()), this, SLOT(sockReady()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));
    qDebug()<<socketDeskriptor<<"Client connected";
    qDebug()<<"Send client connect status - YES";
}

void MyServer::sockReady() { //что получает, когда происходит получение от клиента
    Data = socket->readAll();
    qDebug() << "Select from Client" << Data;


    if(!Data.isEmpty()) { //если что-то получило, то

        QDir server_version(QDir::currentPath());
        QStringList filter;
        filter << "*.json";
        foreach(QFileInfo info, server_version.entryInfoList(filter)) {
            filter.clear();
            filter << info.absoluteFilePath();
        }
        qDebug() << filter;

        QFile file(filter.back()); //сервер заходит в свою папку и получает свою версию
        if (!file.open(QIODevice::ReadOnly))//если версии равные, то он возвр клиенту, что версия актуальна
            return;
        path_to_Download = file.readAll();
        if(QString(Data) == path_to_Download) {
            qDebug() << "Send to Client" << "Actuale";
            socket->write("Actuale");
        }

        else if(Data[0] == 'T') { // если клиент отпр список своих файлов
            QStringList client_data;
            client_data.append(QString(Data).split(" ")); //помещение всего списка клиента
            Data.clear(); //очистить для отправки
            QDir dir_server(QDir::currentPath() + "/themes_interfases"); //сервер заходит в свои темы
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
            socket->write(Data); //записывает свои и помещает в переменную, которую нужно отправить клиенту
        }

        else {
            qDebug() << "Send to Client" << "Need update"; //если неактуальные, то отправляет клиенту сообщение об этом
            socket->write("Need update");
        }
        socket->waitForBytesWritten(100);
    }
}

void MyServer::sockDisc(){ //если отключился клиент
    qDebug()<<"Disconnect";
    socket->deleteLater();
}
