#include "thread.h"
#include "window.h"
#include <QTextCodec>
#include <QMessageBox>

Thread::Thread() : QObject() {

}

void Thread::sockReady() {
    if(socket->waitForConnected(100)) {
        QByteArray testing;

        while (socket->waitForReadyRead(3000))
        {
            while(socket->bytesAvailable() > 0)
            {
                testing.append(socket->readAll());
                socket->flush();
            }
        }



        if(testing != "")
        {
            emit time_load();
            /*QFileInfoList dirContent = QDir(qApp->applicationDirPath() + "/updates").entryInfoList(QStringList()<< "*",QDir::Files);
            for (int i = 0; i < dirContent.size(); ++i) {
                QFile file(dirContent.at(i).filePath());
                file.remove();
            }*/

            QTextCodec *codec = QTextCodec::codecForName("CP866");
            QString s = codec->toUnicode(testing);
            QStringList list = s.split("\n\n\n\n\n");

            for (int i = 0; i < list.size() - 1; i++)
            {
                QFile target;
                target.setFileName("D:/5 semester/OSISP/Lab5/Pacman-build/debug/updates/level" + QString::number(fileNum) + ".dll");

                if (!target.open(QIODevice::WriteOnly | QIODevice::Append)) {
                    qDebug() << "Can't open file for written";
                    return;
                }

                QByteArray output;
                output.append(codec->fromUnicode(list[i]));

                target.write(output);
                target.close();

                output.clear();
                fileNum += 1;
            }
        }

        else
        {
            emit load_end("Установлены последние обновления");
        }
        //share_video();
    }
}

void Thread::sockDisc() {
    socket->disconnected();
}

void Thread::run() {
    socket = new QTcpSocket();
    connect(socket,SIGNAL(readyRead()),this,SLOT(sockReady()));
    socket->connectToHost("127.0.0.1", 5555);
}

/*void Thread::share_video() {

    if(QFile::copy("D:/5 semester/OSISP/Lab5/build-Server-Desktop_Qt_5_15_2_MinGW_32_bit-Debug/debug/video/AQN.mp4",
       "D:/5 semester/OSISP/Lab5/Pacman-build/debug/video/AQN.mp4")) emit load_video(1);
}*/
