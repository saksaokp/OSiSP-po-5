#include "thread.h"

QDir dir_client(QDir::currentPath());

Thread::Thread(QString s) : name(s) {

}

void Thread::sockReady() {
    if(socket->waitForConnected(100)) {
        socket->waitForReadyRead(100);
        Data = socket->readAll();

        QStringList rec_data_update;
        QString new_version;

        rec_data_update.append(QString(Data).split(" "));
        new_version.append(rec_data_update.last());

        path_server = rec_data_update.front();

        QDir new_client_version(QDir::current());
        QStringList filter;
        filter << "*.json";
        foreach(QFileInfo info, new_client_version.entryInfoList(filter)) {
            filter.clear();
            filter << info.absoluteFilePath();
        }

        QFile file(filter.back());
        if (!file.open(QIODevice::WriteOnly))
            return;
        file.write(new_version.toStdString().data());
        QFile::remove(dir_client.path() + '/' + "Colors.txt");
        QFile::copy(rec_data_update.front()+'/'+ "Colors.txt", dir_client.path() + '/' + "Colors.txt");

        //create log

        QDir write_log(QDir::currentPath() + "/logs");
        QStringList formatFile;
        formatFile << "*.txt";
        foreach(QFileInfo info, write_log.entryInfoList(formatFile)) {
            formatFile.clear();
            formatFile << info.absoluteFilePath();
        }

        QFile log(formatFile.front());
        if (!log.open(QIODevice::WriteOnly))
            return;
        QString text = "Update Modules and version "+ rec_data_update.back();
        log.write(text.toStdString().data());
    }
//    sockDisc();
    emit load_update(1);
    share_video();
}

void Thread::sockDisc() {
    socket->disconnected();
}

void Thread::run() {
    socket = new QTcpSocket();
    connect(socket,SIGNAL(readyRead()),this,SLOT(sockReady()));
    socket->connectToHost("127.0.0.1", 1919);

    Data.clear();
    Data.append("Yes");
    socket->write(Data);
    socket->waitForBytesWritten(100);

    emit time_load(58);
}

void Thread::share_video() {

    if(QFile::copy(path_server+"/video/Что такое безумие.mp4", dir_client.path() + "/video/Что такое безумие.mp4")) emit load_video(1);
}
