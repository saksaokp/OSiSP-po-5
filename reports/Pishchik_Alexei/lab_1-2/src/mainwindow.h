#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QLocale>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_processor_clicked(bool checked);
    void result_update(int size_cols, QStringList header, QStringList mass);
    void update_str(string s);
    void read_file_info();
    void on_mother_clicked();

    void on_os_clicked();

    void on_info_programm_clicked();

    void on_ram_clicked();

    void on_hard_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H