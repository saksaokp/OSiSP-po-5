#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include "interface.h"
#include <QTcpSocket>
#include <QMessageBox>
#include <QDir>
#include <QJsonObject>
#include <windows.h>
#include <QPluginLoader>
#include <QDebug>
#include <iostream>
#include <fstream>
#include <string>
#include <QTimer>
#include <QThread>

#include "thread.h"
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

    void load_mode_plugins();

    QTcpSocket* socket;
    QByteArray Data;
    int progress = 0;
    QTimer *timer;

public slots:
    void showProgress(int i);
    void sockReady();
    void sockDisc();
    void loading(int res);
    void download_video(int msg);

private slots:
    void on_processor_clicked(bool checked);
    void result_update(int size_cols, QStringList header, QStringList mass);
    void update_str(string s);
    void on_mother_clicked();
    void on_os_clicked();
    void on_info_programm_clicked();
    void on_ram_clicked();
    void on_hard_clicked();
    void on_apply_clicked();
    void on_reboot_clicked();
    void on_check_update_clicked();

public:
    Ui::MainWindow *ui;
    QList<Interface*> _mode;
    QThread *thread_update;
};

#endif // MAINWINDOW_H
