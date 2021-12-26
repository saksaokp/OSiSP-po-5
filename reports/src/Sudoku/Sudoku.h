#ifndef SUDOKU_H
#define SUDOKU_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QPluginLoader>
#include <fontPluginInterface.h>


typedef void (*AboutFunction)(QWidget* parent);

namespace Ui {
    class Sudoku;
}

class Sudoku : public QMainWindow {
    Q_OBJECT

public:
    explicit Sudoku(QWidget *parent = 0);
    virtual ~Sudoku();
    void loadPlugins();
    int fileNum = 2;
    //int progress = 0;

//signals: void time_load(int);

public slots:
    void changeMode(QAction* action);
    void showProgress(double progress);
    void changeAppFont(QFont font);
   // void showProgress(int i);

private:
    Ui::Sudoku *ui;
    AboutFunction showAboutWindow = nullptr;
    QTcpSocket* socket;
    QString currentVersion;
    bool autoUpdateSetting;
    QAction *actionAutoUpdate;
    bool isAutoUpdate;
    bool upToDate;
    bool shouldShowMessageBox;
    QString messageBoxText;

private slots:
    void about();
    void sockReady();
    void sockDisc();
    void update(bool);
    void setAutoUpdate();
    void writeSettingsToFile();
    QString getAutoUpdateMessage();
};

#endif // SUDOKU_H
