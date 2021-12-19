#ifndef MAZE_H
#define MAZE_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QWidget>
#include <QComboBox>
#include <QPainter>
#include <time.h>
#include <QLibrary>
#include <QString>
#include <QtWidgets>
#include <QMessageBox>
#include "generator.h"
#include "interface.h"

const int BLOCK_SIZE=15;
const int MARGIN=22;
const int AREA_ROW=31;
const int AREA_COL=31;

enum moved
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

QT_BEGIN_NAMESPACE
namespace Ui { class Maze; }
QT_END_NAMESPACE
class Maze : public QMainWindow
{
    Q_OBJECT

public:
    Maze(QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    ~Maze();

    int place_x;
    int place_y;
    int place_finish_x, place_finish_y;
    QVector<QVector<int> > field;

public:
    void SetPlugins();
    void InitGame();
    void InitPause();
    void PauseResumeGame();
    bool IsGameOver();
    void InitMenu();
    void gener();

public slots:
    void on_btn_exit_clicked();

private slots:
    void SnakeUpdate(int key);
    void aboutQt();
    void applyPlugin(int index);
    void on_btn_start_clicked();

private:
    Ui::Maze *ui;
    Ui::Maze *game_win; // окно для игры
    bool flag_game = false;
    bool isPause;
    QList<QPoint> wall;
    QList<QPoint> man;
    moved dir;
    QVector< Interface* > mPlugins;
    int countLevels = 0;
};

#endif // MAZE_H
