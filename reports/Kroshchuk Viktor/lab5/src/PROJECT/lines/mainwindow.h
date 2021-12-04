#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QComboBox>
#include "GameLogic.h"
#include <QGridLayout>
#include "cell.h"
#include "Definitions.h"
#include <QPainter>
#include <QAnimationDriver>
#include <QAnimationGroup>
#include <QGraphicsOpacityEffect>
#include <QButtonGroup>
#include <QFontDatabase>
#include <QMessageBox>
#include <QCloseEvent>
#include <QMainWindow>
#include <QPluginLoader>
#include <QLibrary>
#include <QTcpSocket>
#include <QFileDialog>
#include <QThread>
#include "thread.h"
#include "interface.h"
#include "interface_theme.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    QPushButton* score;
    QString set_name_second;
    QString set_name_first;
    void gameOver();
    void startScreen();
    void startGame();
    void checkUpdate();
    void info();
    void setPlugins();
    void set_interfase_plugins();
    void nextMove();
    QIcon mergedIcon(Ghosts type, MatrixPoint place, bool select = true);
    ~MainWindow();

public slots:
    void showProgress(int i);
   void loading(int res);
   void download_video(int msg);
    void sockDisc();
    void sockReady();
    void applyPlugin(int index);
    void applyTheme(int index);
    void ghostWasSelected(Ghosts type, MatrixPoint place);
    void ghostWasDeselected(Ghosts type, MatrixPoint place);
    void ghostWasGenerated(Ghosts type, MatrixPoint place);
    void ghostWasMoved(std::vector<Node> road, Ghosts type);
    void ghostWasDeleted(MatrixPoint place);
    void finishedAnimating();

    void playButtonWasClicked(bool zrtik);
    void updateButtonWasClicked(bool zrtik);
    void aboutButtonWasClicked(bool zrtik);
    void settingsButtonWasClicked(bool zrtik);
    void homeButtonWasClicked(bool zrtik);

    void buttonWasPressed(QWidget* button);
    void buttonWasReleased(QWidget* button);

signals:
    wasPressed(QWidget* button);
    wasReleased(QPushButton* button);

private:
    QThread *thread_update;
    int progress = 0;
    QWidget* board = new QWidget();
    Cell* **cells;
    Ghosts lastCellType;
    MatrixPoint* lastCellPlace;
    void closeEvent(QCloseEvent *bar);
    Ui::MainWindow *ui;
    QComboBox *list;
    QComboBox *list_theme;
    QVector <Interface*> mPlugin;
    QVector <Interface_theme*> mThemes;
    QTcpSocket* socket;
    QByteArray Data;
};
#endif // MAINWINDOW_H
