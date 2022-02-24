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
            Data.clear();

            Data.append("Yes");
            socket->write(Data);
            socket->waitForBytesWritten(100);
        }
        else {
            QStringList rec_data_update;
            QString new_version;

            rec_data_update.append(QString(Data).split(" "));
            new_version.append(rec_data_update.last());

            QDir new_client_version(QDir::currentPath());
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
            QFile::remove(dir_client.path() + '/' + "Colors.txt");
            QFile::copy(rec_data_update.front()+'/'+ "Colors.txt", dir_client.path() + '/' + "Colors.txt");

            QMessageBox::information(this, "Информация", "Обновление завершено!");

            ui->comboBox->clear();
            lColor.clear();
            setInterfaceColor();

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
    }
}

void Widget::on_comboBox_currentIndexChanged(int index)
{
    QWidget::setStyleSheet(lColor[index]);
}
