#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QTcpSocket>
#include <QDir>
#include <QFile>

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


private slots:
    void on_comboBox_currentIndexChanged(int index);

public:
    Ui::Widget *ui;
    QTcpSocket* socket;
    QByteArray Data;
};

#endif // WIDGET_H
