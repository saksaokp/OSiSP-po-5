#ifndef THREAD_H
#define THREAD_H

#include <QTcpSocket>
#include <QThread>
#include <QTimer>
#include <QDir>
#include <QFile>


class Thread : public QObject
{
    Q_OBJECT
public:
    explicit Thread(QString name);

    QTcpSocket* socket;
    QByteArray Data;
    int progress = 0;
    QTimer *timer;


public slots:
    void sockReady();
    void sockDisc();
    void run();
    void share_video();

signals:
    void time_load(int);
    void load_update(int);
    void load_video(int);

private:
    QString name;
    QString path_server;
};


#endif // THREAD_H
