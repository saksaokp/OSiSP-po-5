#ifndef THREAD_H
#define THREAD_H

#include <QObject>
#include <QTcpSocket>
#include <QThread>
#include <QFile>
#include <QTimer>
#include <QDir>

class Thread : public QObject
{
    Q_OBJECT
public:
    Thread();
    //explicit Thread(QString name);

    QTcpSocket* socket;
    QByteArray Data;
    int progress = 0;
    int fileNum = 2;
    QTimer *timer;

public slots:
    void sockReady();
    void sockDisc();
    void run();
    //void share_video();

signals:
    void time_load();
    //void load_video(int);
    void load_end(QString);

private:

};

#endif // THREAD_H
