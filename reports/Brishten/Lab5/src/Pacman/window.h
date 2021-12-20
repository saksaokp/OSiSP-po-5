#ifndef WINDOW_H
#define WINDOW_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QMenuBar>
#include <QPainter>
#include <QString>
#include <QTimer>
#include <QTime>
#include <QThread>
#include <QStatusBar>
#include <QProgressBar>

#include <QTcpSocket>
#include <QMessageBox>
#include <QDebug>
#include <QListIterator>

#include "pacman.h"
#include "map.h"
#include "ball.h"
#include "ghost.h"
#include "powerball.h"
#include "textdrawing.h"
#include "fontPluginInterface.h"
#include "fontPluginInterface2.h"
#include "thread.h"
#include "dialogwindow.h"

typedef void (*about)(QWidget *painter);

namespace Ui {
class window;
}

class window : public QDialog
{
    Q_OBJECT
    
public:
    explicit window(QWidget *parent = 0);
    void pacman_move();
    void ghostsmove();
    void ghostsmove1();
    void ghostsmove2();
    void moveghostsinrect2();
    void moveghostsinrect1();
    void moveghostsinrect();
    void checklost();
    void delay();
    void start_Game();
    void end_Game();
    void loadPlugins();
    void loadLevel();
    bool getFlag();
    void stopConn();



    QTcpSocket* socket;
    QByteArray Data;

    Pacman *pacman;
    Ghost *ghost;
    Ghost *ghost1;
    Ghost *ghost2;

    Map *pac_map;
    Ball *ball;
    PowerBall *powerball;
    Textdrawing *text;
    about f2;

    int level = 1, fileNum = 2;
    int progress = 0;
    int pacx,pacy,direction,nextdirection;
    int gosx,gosy,ghostdir,nextghostdir;
    int gosx1,gosy1,ghostdir1,nextghostdir1;
    int gosx2,gosy2,ghostdir2,nextghostdir2;
    bool moving,ghostmoving,ghostmoving1,ghostmoving2;
    bool scared,scared1,scared2;
    int score,state3,state2,state1,state;
    bool start,delayb;
    bool ghoststart,ghoststart1,ghoststart2;
    bool playing;
    bool updateAuto = false;
    QVector<QPoint> ballpoints;
    QVector<QPoint> Powerballpoints;
    QThread *sleeper;
    ~window();
public slots:
    void updater();
    void ghostupdater();
    void About();
    void changeAppFont(QFont font);
    void on_pushButton_clicked();
    void sockReady();
    void sockDisc();
    void onRecentOpenFiles(QAction *action);
    void changeLevel(int x);
    void defaultLevel();
    void setFlag();
    void setFlag_2();

    void loading(QString mes);
    void showProgress();
    void Progress();

protected:
    void keyPressEvent(QKeyEvent *event);


private:
    Ui::window *ui;
    QGraphicsScene *scene;
    QTimer *timer, *timer_2;
    QTimer *ghoststimer;
    QMenuBar *menuBar;
    QMenu *style, *updated, *levelMenu;
    QThread *Update;
    DialogWindow dialog;
    QProgressBar* bar;
};

#endif // WINDOW_H
