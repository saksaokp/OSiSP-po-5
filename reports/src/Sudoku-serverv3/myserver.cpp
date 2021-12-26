#include "myserver.h"
#include <QTcpSocket>
#include <QFile>
#include <QDir>

myserver::myserver() {}

myserver::~myserver() {}

void myserver::startServer()
{
    if (this->listen(QHostAddress::Any, 5555))
    {
        qDebug() << "Listening";
    }
    else
    {
        qDebug() << "Not listening";
    }
}

void myserver::incomingConnection(long long socketDescriptor)
{
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket, SIGNAL(readyRead()), this, SLOT(sockReady()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(sockDisc()));

    qDebug() << socketDescriptor << "Client connected";
}

void myserver::sockReady()
{
    QByteArray data = socket->readAll();
    qDebug() << "Received client version: " << data;

    QFile updatesFile(qApp->applicationDirPath() + "/updates.json");
    updatesFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray updatesFileData = updatesFile.readAll();
    updatesFile.close();

    QJsonDocument updatesDoc = QJsonDocument::fromJson(updatesFileData);
    QJsonObject rootObj = updatesDoc.object();
    QString currentVersion = rootObj.value("currentVersion").toString();

    if (data == currentVersion)
    {
        socket->write("Up-to-date");

        return;
    }

    QJsonArray updates = rootObj.value("updates").toArray();
    QByteArray dataToSend;

    foreach (const QJsonValue& update, updates)
    {
        if (update.toObject().value("fromVersion").toString() == data)
        {
            dataToSend.append(currentVersion.toStdString().c_str());

            QJsonArray changes = update.toObject().value("changes").toArray();

            foreach (const QJsonValue& pathToChangedFile, changes)
            {
                dataToSend.append("\n\n\n");
                dataToSend.append(pathToChangedFile.toString().toStdString().c_str());
                dataToSend.append("\n\n\n");

                QFile fileToSend(qApp->applicationDirPath() + pathToChangedFile.toString());
                fileToSend.open(QIODevice::ReadOnly);
                QByteArray fileContents = fileToSend.readAll();
                dataToSend.append(fileContents);
            }
            qDebug() << dataToSend.size();
            socket->write(dataToSend);

            return;
        }
    }
}

void myserver::sockDisc()
{
    qDebug() << "Disconnect";
    socket->deleteLater();
}
