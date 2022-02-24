#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QTcpSocket>
#include <QThread>
#include "thread.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void setScene( QGraphicsScene *scene);

    QStringList lColor;
    void setInterfaceColor();

public slots:
    void score(int s);
    void fUpdate();
    void sockDisc();
    void sockReady();
    void showProgress(int i);
   void loading(int res);
   void download_video(int msg);


private slots:
    void on_comboBox_currentIndexChanged(int index);

public:
    Ui::Widget *ui;
    QTcpSocket* socket;
    QByteArray Data;
    int progress = 0;
};

#endif // WIDGET_H
