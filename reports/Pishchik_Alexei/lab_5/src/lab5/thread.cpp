#include "thread.h"

Thread::Thread(QString s) : name(s) {

}

void Thread::sockReady() {
    if(socket->waitForConnected(100)) {
        socket->waitForReadyRead(100);
        Data = socket->readAll();

        QStringList rec_data_update;
        std::ofstream write_json_clien;
        QString new_version;

        rec_data_update.append(QString(Data).split(" "));
        new_version.append(rec_data_update.last());

        write_json_clien.open("C:\\Users\\Toketsu\\Desktop\\QT_3 _lab\\lab1\\debug\\client.json");
        write_json_clien << new_version.toStdString();
        write_json_clien.close();


        for(int i = 0; i < rec_data_update.size()-1; i++) {
            QFile::copy("C:\\Users\\Toketsu\\Desktop\\test server\\server\\server\\debug\\plugins\\"+rec_data_update[i], "C:\\Users\\Toketsu\\Desktop\\QT_3 _lab\\lab1\\debug\\plugins\\"+rec_data_update[i]);
        }

        //create log
            std::ofstream write_log;
            write_log.open("C:/Users/Toketsu/Desktop/test server/server/server/debug/logs/log.txt", std::ios::app);
            write_log << std::endl;
            write_log << "Update Modules and version " << QString(Data).toStdString();
            write_log.close();
    }
    sockDisc();
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

    QByteArray wr;
    QStringList find_filter;
    QDir dir_client(QDir::current());
    dir_client.cd("plugins");
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
        wr.append(str);
        if(&str != find_filter.last()) {
            wr.append(" ");
        }
    }
    qDebug() << wr << endl; //get list plugins client


    socket->write(wr);
    socket->waitForBytesWritten(100);

    emit time_load(58);
}

void Thread::share_video() {
    if(QFile::copy("D:\\DCs.Legends.of.Tomorrow.S06E11.1080p.rus.LostFilm.TV.mkv", "C:\\Users\\Toketsu\\Desktop\\QT_3 _lab\\lab1\\debug\\video\\DCs.Legends.of.Tomorrow.S06E11.1080p.rus.LostFilm.TV.mkv")) emit load_video(1);
}
