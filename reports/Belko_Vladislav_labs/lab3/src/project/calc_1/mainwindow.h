#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <math.h>
#include <string>
#include <QDialog>
#include <QMessageBox>
#include <QLibrary>
#include <QDebug>
#include <QDir>
#include <QPluginLoader>
#include "interface.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void load_mode_plugins();
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void Two_Ten();
    void Eight_Ten();
    void Two_Six();
    void Eight_Six();
    void Ten_Six();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void applyPlugin(int index);

private:
    Ui::MainWindow *ui;
    int Flag = 0;
    int Value = 0;
    QVector< Interface* > mPlugins;
};
#endif // MAINWINDOW_H
