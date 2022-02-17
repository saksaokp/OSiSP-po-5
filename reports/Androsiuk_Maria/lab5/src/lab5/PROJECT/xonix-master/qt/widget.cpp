#include "widget.h"
#include "ui_widget.h"
#include <QLibrary>
#include <QMessageBox>
#include <QComboBox>

typedef QString (*Helper_set_name_window)();
typedef QString (*Helper_set_first_name)();
typedef QString (*Helper_set_second_name)();

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{

    ui->setupUi(this);
    setInterfaceColor();
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

void Widget::setInterfaceColor()
{
    QFile lev(QDir::currentPath() + "/Colors.txt");
    lev.open(QIODevice::ReadOnly);
    QStringList fileData;
    fileData.append(QString(lev.readLine()).split('_'));
    lev.close();
    int countLev = fileData.front().toInt();
    for (int var = 1; var < fileData.size(); ++var) {
        lColor.append(fileData[var]);
    }
    for (int var = 1; var <= countLev; ++var) {
        ui->comboBox->addItem("Theme" + QString::number(var));
    }
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

void Widget::fUpdate()
{
    QMessageBox msg;

    socket = new QTcpSocket();
    connect(socket,SIGNAL(readyRead()),this,SLOT(sockReady()));

    Data.clear();

    QDir client_version(QDir::currentPath());
    QStringList filter;
    filter << "*.json";
    foreach(QFileInfo info, client_version.entryInfoList(filter)) {
        filter.clear();
        filter << info.absoluteFilePath();
    }
    QFile file(filter.back());
    if (!file.open(QIODevice::ReadOnly))
        return;
    Data = file.readAll();
    socket->connectToHost("127.0.0.1", 1919);
    socket->waitForConnected(1);
    if(socket->state() == QTcpSocket::ConnectedState) {
        if(socket->isOpen()) {
            socket->write(Data);

            socket->waitForBytesWritten(100);
        }
    }
    else {
        msg.setWindowTitle("Информация");
        msg.setText("Соединение не установлено");
        msg.exec();
    }
}

void Widget::sockDisc()
{
    socket->disconnected();
}

void Widget::sockReady()
{
    if(socket->waitForConnected(100)) {
        socket->waitForReadyRead(100);
        Data = socket->readAll();

         QDir dir_client(QDir::currentPath());

        if(Data == "Actuale") {
            QMessageBox::information(this, "Информация", "Соединение установлено\nУ вас актуальная версия программы!");
            socket->disconnected();
        }

        else if(Data == "Need update") {

            QMessageBox msg;
            msg.setText("New version is available");
            msg.setInformativeText("Do you want to update app?");
            msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            msg.setDefaultButton(QMessageBox::Yes);
            int res = msg.exec();

            //loading

            if (res == QMessageBox::Yes) {
                sockDisc();
                socket->waitForDisconnected(1);


                QThread *thread= new QThread;
                Thread *my = new Thread("B");

                my->moveToThread(thread);

                connect(my, SIGNAL(time_load(int)), this, SLOT(showProgress(int)));
                connect(my, SIGNAL(load_update(int)), this, SLOT(loading(int)));
                connect(my, SIGNAL(load_video(int)), this, SLOT(download_video(int)));

                connect(thread, SIGNAL(started()), my, SLOT(run()));

                thread->start();
            }
        }
    }
}

void Widget::on_comboBox_currentIndexChanged(int index)
{
    QWidget::setStyleSheet(lColor[index]);
}

void Widget::loading(int res) {
    if(res == 1) {
        for(int i =0; i <= ui->comboBox->count(); i++ ) {
            ui->comboBox->removeItem(i);
        }
        lColor.clear();
        setInterfaceColor();
        ui->comboBox->removeItem(0);
    }
}

void Widget::showProgress(int i) {
    progress = i;
    ui->label->setText(QString::number(progress)+"%");
    ui->label->setText("100%");
    QMessageBox::information(this, "Информация", "Обновление завершено!");
}

void Widget::download_video(int msg) {
    if(msg == 1) QMessageBox::information(this, "Информация", "Видео получено!");
}
