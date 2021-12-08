#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    typedef QString (*Helper_set_name_window)();
    typedef QString (*Helper_set_name_about)();
    typedef QString (*Helper_set_name_btn)();

    ui->setupUi(this);

    load_mode_plugins();
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

void MainWindow::applyPlugin(int index) {
    QFont pallete = this->mPlugins[index]->changeView();
    QApplication::setFont(pallete);
}
