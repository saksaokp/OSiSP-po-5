#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QDialog>
#include <QComboBox>
#include "interface.h"

const int BLOCK_SIZE=15;
const int MARGIN=22;
const int AREA_ROW=30;
const int AREA_COL=30;

const int TIME_INTERVAL=100;


enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT



public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    virtual void paintEvent(QPaintEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    QDialog dlg;
    QComboBox* modeMenu = new QComboBox;

public:
    void InitMenu();
    void SetPlugins();
    void InitGame();
    void InitPause();
    void PauseResumeGame();
    void GameOver();
    void GenerateFood();
    void GenerateSnake();
    bool IsGameOver();

private slots:
    void SnakeUpdate();
    void aboutQt();
    void applyPlugin(int index);
    void BtnDlgClick1();
    void BtnDlgClick2();
    void BtnDlgClick3();
    void LoadingLevel();
    void CheckUpdate();

private:
    Ui::MainWindow*ui;
    QTimer *gameTimer;
    bool isPause;
    QPoint foodPoint;
    QList<QPoint> wall;
    QList<QPoint> snake;
    Direction dir;
    int score;
    int level;
    QVector< Interface* > mPlugins;
};

#endif // MAINWINDOW_H
