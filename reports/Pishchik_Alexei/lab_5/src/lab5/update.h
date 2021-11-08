#ifndef UPDATE_H
#define UPDATE_H

#include <QObject>

class update : public QObject
{
    Q_OBJECT
public:
    explicit update(QObject *parent = nullptr);

    void run();

signals:

};

#endif // UPDATE_H
