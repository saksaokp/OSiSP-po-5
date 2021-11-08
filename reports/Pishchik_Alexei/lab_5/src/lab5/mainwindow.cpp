#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "helper.h"
#include "about.h"
#include <QThread>
#include <QDebug>
#include "thread.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    AllocConsole();
    ShowWindow(GetConsoleWindow(), SW_HIDE); // hide console

    ui->setupUi(this);
    ui->tableWidget->setEditTriggers(0);
    bool checked = true;
    on_processor_clicked(checked);
    load_mode_plugins();


    //connect(&thread_update, &QThread::started, &th_one, &UPDATE::run);

    //th_one.moveToThread(&thread_update);

}

string *res = new string[100];
QStringList header, result_data, mass;
int size_str = 0;

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::load_mode_plugins()
{
    QDir dir(qApp->applicationDirPath());
    dir.cd("plugins");
    QStringList filter;
    filter << "*.dll";
    QPluginLoader loader;
    foreach(QFileInfo info, dir.entryInfoList(filter)) {
        loader.setFileName(info.absoluteFilePath());
        Interface* mode = qobject_cast<Interface*>(loader.instance());
        if(mode) {
            QString name = loader.metaData().value("MetaData").toObject().value("Mode_name").toString();
            qDebug() << name;
            ui->mode_list->addItem(name);
            _mode.append(mode);
        }
    }
}

void MainWindow::result_update(int size_cols, QStringList header, QStringList mass) {
    string result[size_cols];
    string s;
    ifstream f1;
    f1.open("test1.txt");
    int i = 0;
    while (!f1.eof()) {
        getline(f1, s);
        result[i] = s;
        i++;
    }
    f1.close();
    Helper a;
    a.destroy_file("test1.txt");
    for (int i = 0; i < size_cols; i++)
    {
        res[i] = result[i];
    }
    ui->tableWidget->setRowCount(size_cols); // Устанавливаем количество строк на size_cols
    ui->tableWidget->setColumnCount(1);
    for(int i = 0; i < size_cols; i++) {
        ui->tableWidget->verticalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget->setVerticalHeaderLabels(header);
    ui->tableWidget->horizontalHeader()->setVisible(false);
    for(int i = 0; i < size_cols; i++) {
        QString data = QString::fromStdString(res[i]);
        result_data.append(data);
    }

    int countt = 0;
    for (int i = countt; i <  ui->tableWidget->rowCount(); ++i) {
        QTableWidgetItem * item;
        for (int j = 0; j < ui->tableWidget->columnCount(); ++j) {
            item = new QTableWidgetItem;
            for(int s = 0; s < size_str; s++) {
                if(i==s)
                   item->setText(result_data.value(mass[s].toInt()));
                ui->tableWidget->setItem(i, j, item);
            }
        }
    }
    countt++;

    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();
}

void MainWindow::update_str(string s) {
    string new_str;
    bool flag = false;
    int flag1 = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '|') {
            flag = false;
            flag1++;
        }
        if (flag1 == 1) {
            new_str += '\n';
            flag1++;
        }
        if (flag == true) {
            new_str += s[i];
        }
        if (s[i] == '\n' || (s[i] == ' ' && s[++i] == ' ')) {
            flag = false;
        }
        if (s[i] == '=') {
            size_str++;
            flag = true;
        }
    }
    ofstream ff;
    ff.open("test1.txt");
    ff << new_str;
    ff.close();
}

void MainWindow::on_processor_clicked(bool checked) {
    size_str = 0;
    ui->tableWidget->setVisible(true);
    ui->switch_info->setText("Информация о процессоре");
    header.clear(), result_data.clear(), mass.clear();
    Helper d;
    const char *take = d.set_apply_do(0).data(); //proc
    system(take);
    Helper a;
    update_str(a.read_file_info());
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(0);
    for(int i = 0; i < size_str; i++) {
        QString m = QVariant(i).toString();
        mass.append(m);
    }
    result_update(size_str, header<<"Частота на ядро"<<"Имя процессора"<<"Количество ядер"<<"Количество потоков", mass);
}

void MainWindow::on_mother_clicked() {
    size_str = 0;
    ui->tableWidget->setVisible(true);
    header.clear(), result_data.clear(), mass.clear();
    ui->switch_info->setText("Информация о Материнской плате");
    Helper d;
    const char *take = d.set_apply_do(1).data(); //mather
    system(take);
    Helper a;
    update_str(a.read_file_info());
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(0);
    for(int i = 0; i < size_str; i++) {
        QString m = QVariant(i).toString();
        mass.append(m);
    }
    result_update(size_str, header<<"Производитель"<<"Модель", mass);
}

void MainWindow::on_os_clicked() {
    size_str = 0;
    ui->tableWidget->setVisible(true);
    header.clear(), result_data.clear(), mass.clear();
    ui->switch_info->setText("Информация об Операционной системе");
    Helper d;
    const char *take = d.set_apply_do(4).data();  //OS
    system(take);
    Helper a;
    update_str(a.read_file_info());
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(0);
    for(int i = 0; i < size_str; i++) {
        QString m = QVariant(i).toString();
        mass.append(m);
    }
    result_update(size_str, header<<"Производитель OS"<<"Версия", mass);
}

void MainWindow::on_ram_clicked() {
    size_str = 0;
    ui->tableWidget->setVisible(true);
    header.clear(), result_data.clear(), mass.clear();
    ui->switch_info->setText("Информация об Модулях оперативной памяти");
    Helper d;
    const char *take = d.set_apply_do(2).data(); //ram
    system(take);
    Helper a;
    update_str(a.read_file_info());
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(0);
    int r = size_str/2;
    for(int i = 0; i < r; i++) {
        header<<"Партийный номер"<<"Частота";
    }
    for(int i = 0; i < size_str; i++) {
        QString m = QVariant(i).toString();
        mass.append(m);
    }
    result_update(size_str, header, mass);
}

void MainWindow::on_hard_clicked() {
    size_str = 0;
    ui->tableWidget->setVisible(true);
    header.clear(), result_data.clear(), mass.clear();
    ui->switch_info->setText("Информация об Накопителях");
    Helper d;
    const char *take = d.set_apply_do(3).data(); //hard
    system(take);
    Helper a;
    update_str(a.read_file_info());
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(0);
    int r = size_str/2;
    for(int i = 0; i < r; i++) {
        header<<"Модель"<<"Размер";
    }
    for(int i = 0; i < size_str; i++) {
        QString m = QVariant(i).toString();
        mass.append(m);
    }
    result_update(size_str, header, mass);
}

void MainWindow::on_info_programm_clicked() {
    About ab(this);
    ab.exec();
}

void MainWindow::on_apply_clicked() {
    QApplication::setFont(_mode.at(ui->mode_list->currentIndex())->changeView());
}

void MainWindow::on_reboot_clicked() {
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

void MainWindow::on_check_update_clicked() {

    socket = new QTcpSocket();
    connect(socket,SIGNAL(readyRead()),this,SLOT(sockReady()));

    Data.clear();
    string result_client;
    ifstream f;
    f.open("C:\\Users\\Toketsu\\Desktop\\QT_3 _lab\\lab1\\debug\\client.json");
    getline(f, result_client);
    f.close();
    QString data_client = QString::fromStdString(result_client);
    Data.append(data_client);
    socket->connectToHost("127.0.0.1", 5555);
    socket->waitForConnected(1);
    if(socket->state() == QTcpSocket::ConnectedState) {
        if(socket->isOpen()) {
            socket->write(Data);

            socket->waitForBytesWritten(100);
        }
    }
    else {
        QMessageBox::information(this, "Информация", "Соединение не установлено");
    }
}

void MainWindow::sockReady() {
    if(socket->waitForConnected(100)) {
        socket->waitForReadyRead(100);
        Data = socket->readAll();

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

void MainWindow::sockDisc() {
    socket->disconnected();
}


void MainWindow::loading(int res) {
    if(res == 1) {
        _mode.clear();
        ui->mode_list->clear();
        load_mode_plugins();
    }
}

void MainWindow::showProgress(int i) {
    progress = i;
    ui->statusbar->showMessage(QString::number(progress)+"%");
    ui->statusbar->showMessage("100%");
    QMessageBox::information(this, "Информация", "Обновление завершено!");
}


void MainWindow::download_video(int msg) {
    if(msg == 1) QMessageBox::information(this, "Информация", "Видео получено!");
}


