#ifndef SNAKE_H
#define SNAKE_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QWidget>
#include <QThread>
#include "thread.h"
#include <QComboBox>
#include <QPainter>
#include <QTcpSocket>
#include <time.h>
#include <QLibrary>
#include <QTimer>
#include <QString>
#include <QtWidgets>
#include <QMessageBox>
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
    RIGHT,
};

QT_BEGIN_NAMESPACE
namespace Ui { class Snake; }
QT_END_NAMESPACE
class Snake : public QMainWindow
{
    Q_OBJECT

public:
    Snake(QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    ~Snake();

public:
    QThread *thread_update;
    int progress = 0;
    void SetPlugins();
    void Setlevels();
    void InitGame();
    void InitPause();
    void PauseResumeGame();
    void GameOver();
    void GenerateFood();
    void GenerateSnake();
    bool IsGameOver();
    void InitMenu();

public slots:
    void on_btn_exit_clicked();
    void on_btn_update_clicked();
    void sockDisc();
    void sockReady();

private slots:
    void SnakeUpdate();
    void aboutQt();
    void applyPlugin(int index);
    void on_btn_start_clicked();
    void on_levelslist_currentIndexChanged(const QString &arg1);
    void showProgress(int i);
    void loading(int res);
    void download_video(int msg);

private:

    Ui::Snake*ui;
    Ui::Snake*game_win; // окно для игры
    bool flag_game = false;
    QTimer *gameTimer;
    bool isPause;
    QPoint foodPoint;
    QList<QPoint> wall;
    QList<QPoint> snake;
    Direction dir;
    int score = 0;
    QString level;
    QVector< Interface* > mPlugins;
    QStringList levels;
    QTcpSocket* socket;
    int countLevels = 0;
    QByteArray Data;
};

#endif // SNAKE_H
