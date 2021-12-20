#include "myserver.h"

myserver::myserver(){}

myserver::~myserver(){}

void myserver::startServer()
{
    if (this->listen(QHostAddress::Any,5555))
    {
        qDebug()<<"Listening";
    }
    else
    {
        qDebug()<<"Not listening";
    }

}

void myserver::incomingConnection(int socketDescriptor)
{
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);

        connect(socket,SIGNAL(readyRead()),this,SLOT(sockReady()));
        connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));

    qDebug()<<socketDescriptor<<" Client connected";

    QByteArray data;

    QFileInfoList dirContent = QDir(qApp->applicationDirPath() + "/plugins").entryInfoList(QStringList()<< "*",QDir::Files);
    for (int i = 0; i < dirContent.size(); ++i) {
        QFileInfo fileInfo = dirContent.at(i);
        QString fileName = dirContent.at(i).fileName();
        qDebug() << fileName;
        QFile file(dirContent.at(i).filePath());
        file.open(QIODevice::ReadOnly);
        data += file.readAll();
        data += "\n\n\n\n\n";
        file.remove();
    }

    if(data.isEmpty())
    {
        data = "empty";
    }
    socket->write(data);
    qDebug()<<"Send client connect status - YES";
}

void myserver::sockReady()
{

}

void myserver::sockDisc()
{
    qDebug()<<"Disconnect";
    socket->deleteLater();
}
