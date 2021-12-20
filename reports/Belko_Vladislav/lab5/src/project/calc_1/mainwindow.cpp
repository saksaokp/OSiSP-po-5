#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    typedef QString (*Helper_set_name_window)();
    typedef QString (*Helper_set_name_about)();
    typedef QString (*Helper_set_name_btn)();

    ui->setupUi(this);

    load_mode_plugins();
    load_interface_plugins();
    // установка имени окна приложения
    QLibrary *helper_set = new QLibrary("Helper");
    Helper_set_name_window set_window_name_ = (Helper_set_name_window)helper_set->resolve("set_window_name");
    QString windowTitle = set_window_name_();
    delete helper_set;
    this->setWindowTitle(windowTitle);

    // установка имени кнопки
    QLibrary *helper_set_n_btn = new QLibrary("Helper");
    Helper_set_name_btn set_btn_name_ = (Helper_set_name_btn)helper_set_n_btn->resolve("set_window_btn_name");
    ui->pushButton->setText(set_btn_name_());
    delete helper_set_n_btn;

    // установка имени About
    QLibrary *helper_set_n_about = new QLibrary("Helper");
    Helper_set_name_about set_window_name_first = (Helper_set_name_about)helper_set_n_about->resolve("set_name_About");
    ui->pushButton_7->setText(set_window_name_first());
    delete helper_set_n_about;
}

void MainWindow::load_mode_plugins() {
    QDir dir(qApp->applicationDirPath());
    dir.cd("plugins");
    QStringList filter;
    filter << "*.dll";
    QPluginLoader loader;
    foreach(QFileInfo info, dir.entryInfoList(filter)) {
        loader.setFileName(info.absoluteFilePath());
        Interface* mode = qobject_cast<Interface*>(loader.instance());
        if(mode) {
            this->mPlugins.push_back(mode);
            QString name = loader.metaData().value("MetaData").toObject().value("Mode_name").toString();
            ui->comboBox->addItem(name);
            connect(ui->comboBox, SIGNAL(activated(int)), this, SLOT(applyPlugin(int)));
        }
    }
}

void MainWindow::load_interface_plugins() {
    QDir dir(qApp->applicationDirPath());
    dir.cd("themes_interfases");
    QStringList filter_1;
    filter_1 << "*.dll";
    QPluginLoader loader_1;
    foreach(QFileInfo info, dir.entryInfoList(filter_1)) {
        loader_1.setFileName(info.absoluteFilePath());
        Interface_theme* mode1 = qobject_cast<Interface_theme*>(loader_1.instance());
        if(mode1) {
            this->mTheme.push_back(mode1);
            QString name1 = loader_1.metaData().value("MetaData").toObject().value("interfas_name").toString();
            ui->comboBox_2->addItem(name1);
            connect(ui->comboBox_2, SIGNAL(activated(int)), this, SLOT(applyPlugin_theme(int)));
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Two_Ten() {
   if(Flag==1) {
        QString inputNum = ui->lineEdit->text();
        QByteArray ba = inputNum.toLocal8Bit();
        char *s= ba.data();
        char *end;
        long a = strtol (s, &end, 2);
        QString num = QString::number(a);
        ui->lineEdit->setText(num);
    }
}

void MainWindow::Two_Six() {
    if(Flag==1) {
        QString inputNum = ui->lineEdit->text();
        QByteArray ba = inputNum.toLocal8Bit();
        char *s= ba.data();
        char *end;
        long a = strtol (s, &end, 2);

        string digits[16] = {"0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F"};
        string hex;
        do {
            hex.insert (0, digits[a % 16]);
            a /= 16;
        }
        while (a!=0);
        QString num = QString::fromUtf8((hex).c_str());
        ui->lineEdit->setText(num);
    }

}

void MainWindow::Eight_Six(){
    if(Flag==2) {
        QString inputNum = ui->lineEdit->text();
        string numb = inputNum.toUtf8().constData();
        int res = 0;
        for (int i = 0; i < (int)numb.size(); ++i) {
            res *= 8;
            res += (numb[i] - '0');
        }

        string digits[16] = {"0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F"};
        string hex;
        do {
            hex.insert (0, digits[res % 16]);
            res /= 16;
        }
        while (res!=0);
        QString num = QString::fromUtf8((hex).c_str());
        ui->lineEdit->setText(num);
    }
}

void MainWindow::Ten_Six(){
    if (Flag==3) {
        QString inputNum = ui->lineEdit->text();
        QByteArray ba = inputNum.toLocal8Bit();
        char *s= ba.data();
        char *end;
        long a = strtol (s, &end, 10);

        string digits[16] = {"0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F"};
        string hex;
        do {
            hex.insert (0, digits[a % 16]);
            a /= 16;
        }
        while (a!=0);
        QString num = QString::fromUtf8((hex).c_str());
        ui->lineEdit->setText(num);
    }
}

void MainWindow::Eight_Ten() {
    if(Flag==2) {
        QString inputNum = ui->lineEdit->text();
        string numb = inputNum.toUtf8().constData();
        int res = 0;
        for (int i = 0; i < (int)numb.size(); ++i) {
            res *= 8;
            res += (numb[i] - '0');
        }
        QString num = QString::fromUtf8(to_string(res).c_str());
        ui->lineEdit->setText(num);
    }
}

void MainWindow::on_pushButton_clicked()
{
    Flag = 1;
}


void MainWindow::on_pushButton_2_clicked() {
    Flag = 2;
}


void MainWindow::on_pushButton_3_clicked() {
    Flag = 3;
}


void MainWindow::on_pushButton_4_clicked() {
    Value = 1;
    if(Flag==1) {
        Two_Six();
    } else if (Flag==2) {
        Eight_Six();
    } else if (Flag==3) {
        Ten_Six();
    }
}

void MainWindow::on_pushButton_5_clicked() {
    Value = 2;
    if(Flag==1) {
         Two_Ten();
    } else if (Flag==2) {
        Eight_Ten();
    }
}

void MainWindow::on_pushButton_6_clicked() {
    ui->lineEdit->clear();
}


void MainWindow::on_pushButton_7_clicked() {
    typedef void (*about)();
    QLibrary *aboutLib = new QLibrary("about");
    about showWindowAboutProgramm = (about)aboutLib->resolve("about");
    showWindowAboutProgramm();
    delete aboutLib;
}

void MainWindow::sockDisc() {
    socket->disconnected();
}

void MainWindow::sockReady() {
    if(socket->waitForConnected(100)) {
        socket->waitForReadyRead(100);
        Data = socket->readAll();

         QDir dir_client(QDir::currentPath() + "/themes_interfases");

        if(Data == "Actuale") {
            QMessageBox::information(this, "Информация", "Соединение установлено\nУ вас актуальная версия программы!");
            socket->disconnected();
        }

        else if(Data == "Need update") {
            Data.clear();
            QStringList find_filter;

            bool ok = dir_client.exists();
            if (ok) {
                dir_client.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
                dir_client.setSorting(QDir::Name);
                QFileInfoList list = dir_client.entryInfoList();

                for (int i = 0; i < list.size(); ++i) {
                    QFileInfo fileInfo = list.at(i);
                    find_filter.append(fileInfo.fileName());
                }
                qDebug() << find_filter << endl;
            }
            foreach (const QString &str, find_filter) {
                Data.append(str);
                if(&str != find_filter.last()) {
                    Data.append(" ");
                }
            }
            qDebug() << Data << endl;


            socket->write(Data);
            socket->waitForBytesWritten(100);
        }
        else {
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

void MainWindow::applyPlugin(int index) {
    QFont pallete = this->mPlugins[index]->changeView();
    QApplication::setFont(pallete);
}

void MainWindow::applyPlugin_theme(int index) {
    QPalette theme = this->mTheme[index]->changeInterfase();
    QApplication::setPalette(theme);
}

void MainWindow::loading(int res) {
    if(res == 1) {
        mTheme.clear();
        ui->comboBox_2->clear();
        load_interface_plugins();
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

void MainWindow::on_pushButton_8_clicked() {
    QMessageBox msg;

    socket = new QTcpSocket();
    connect(socket,SIGNAL(readyRead()),this,SLOT(sockReady()));

    Data.clear();

    QDir client_version(qApp->applicationDirPath());
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
    socket->connectToHost("127.0.0.1", 5555);
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
