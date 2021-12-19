#include "thread.h"

QDir dir_client(QDir::currentPath() + "/themes_interfases");

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

        for(int i = 1; i < rec_data_update.size()-1; i++) {
            QFile::copy(rec_data_update.front()+'/'+rec_data_update[i], dir_client.path()+'/'+rec_data_update[i]);
        }

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
    socket->connectToHost("127.0.0.1", 5555);

    Data.clear();
    QStringList find_filter;

    bool ok = dir_client.exists();
    if (ok) {
        dir_client.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
        dir_client.setSorting(QDir::Name);
        QFileInfoList list = dir_client.entryInfoList();

        for (int i = 0; i < list.size(); ++i) {
            QFileInfo fileInfo = list.at(i);
            find_filter.append(fileInfo.fileName());
        }
        qDebug() << find_filter << endl;
    }
    foreach (const QString &str, find_filter) {
        Data.append(str);
        if(&str != find_filter.last()) {
            Data.append(" ");
        }
    }
    qDebug() << Data << endl; //get list themes_interfases client


    socket->write(Data);
    socket->waitForBytesWritten(100);

    emit time_load(58);
}

void Thread::share_video() {

    if(QFile::copy(path_server+"/video/DCs.Legends.of.Tomorrow.S06E11.1080p.rus.LostFilm.TV.mkv", dir_client.path() + "/video/DCs.Legends.of.Tomorrow.S06E11.1080p.rus.LostFilm.TV.mkv")) emit load_video(1);
}
