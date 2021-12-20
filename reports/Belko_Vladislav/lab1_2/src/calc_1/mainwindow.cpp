#include "mainwindow.h"
#include "ui_mainwindow.h"

int Flag = 0;
int Value = 0;
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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


void MainWindow::on_pushButton_2_clicked()
{
    Flag = 2;
}


void MainWindow::on_pushButton_3_clicked()
{
    Flag = 3;

}


void MainWindow::on_pushButton_4_clicked()
{
    Value = 1;
    if(Flag==1){
        Two_Six();
    } else if (Flag==2){
        Eight_Six();
    } else if (Flag==3) {
        Ten_Six();
    }
}


void MainWindow::on_pushButton_5_clicked()
{
    Value = 2;
    if(Flag==1){
         Two_Ten();
    } else if (Flag==2) {
        Eight_Ten();
    }
}


void MainWindow::on_pushButton_6_clicked()
{
    ui->lineEdit->clear();
}


