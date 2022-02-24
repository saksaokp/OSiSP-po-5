#include "widget.h"
#include "ui_widget.h"
#include <QLibrary>

typedef QString (*Helper_set_name_window)();
typedef QString (*Helper_set_first_name)();
typedef QString (*Helper_set_second_name)();

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{

    ui->setupUi(this);
    // установка имени окна приложения
    QLibrary *helper_set = new QLibrary("Helper");
    Helper_set_name_window set_window_name_ = (Helper_set_name_window)helper_set->resolve("set_window_name");
    QString windowTitle = set_window_name_();
    delete helper_set;
    this->setWindowTitle(windowTitle);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setScene(QGraphicsScene *scene)
{
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(scene->sceneRect());
}

void Widget::score(int s)
{
    // установка имени первого заголовка
    QLibrary *helper_set_f_n = new QLibrary("Helper");
    Helper_set_first_name set_window_name_first = (Helper_set_first_name)helper_set_f_n->resolve("set_first_name_HeaderLabels");
    QString set_name_first = set_window_name_first();
    delete helper_set_f_n;


    // установка имени второго заголовка
    QLibrary *helper_set_s_n = new QLibrary("Helper");
    Helper_set_second_name set_window_name_second = (Helper_set_second_name)helper_set_s_n->resolve("set_second_name_HeaderLabels");
    QString set_name_second = set_window_name_second();
    delete helper_set_s_n;
    ui->lScore->setText(set_name_first + set_name_second + ' ' + QString::number(100-s) + "%");
}
