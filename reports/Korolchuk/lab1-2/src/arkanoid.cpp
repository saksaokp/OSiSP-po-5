#include <QPainter>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QPalette>
#include <QDialog>
#include <QLabel>
#include "arkanoid.h"

Arkanoid::Arkanoid(QWidget *parent)
    : QMainWindow(parent)
{
    aboutGame = new QDialog(this);
    aboutGame->setWindowTitle("Info about game");
    aboutGame->setModal(true);
    aboutGame->setFixedSize(650, 200);

    QLabel *info = new QLabel("Приветствую.\n"
                              "В данной игре вам необходимо разбить все блоки для победного завершения.\n"
                              "У вас есть управляемая ракетка, которая может двигаться влево и вправо.\n"
                              "Вам нужно двигать ракеткой так, чтобы она отбивала мяч, разрушающий блоки.\n"
                              "У вас есть возможность 2 раза пропустить мяч и продолжить игру.\n"
                              "После 3 пропуска мяча игра считается проигранной.\n"
                              "Количество очков, которое вы получаете при разбитии блоков, можно узнать после завершения партии.\n"
                              "Вы можете начать новую игру или узнать о программе через меню.\n"
                              "Также вы можете использовать паузу на клавишу \"p\".\n"
                              "Начать игру можно нажав \"space\".\n"
                              "Корольчук Артём (3 курс, группа ПО-5)", aboutGame);
    info->adjustSize();

    QAction *restart = new QAction("&Restart", this);
    QAction *about = new QAction("&About", this);

    QMenu *actions;
    menuBar()->setFixedHeight(30);

    actions = menuBar()->addMenu("&Actions");
    actions->addAction(restart);
    actions->addAction(about);

    connect(restart, &QAction::triggered, this, &Arkanoid::resetGame);
    connect(about, &QAction::triggered, this, &Arkanoid::aboutProg);

    score = 0;
    fails = 0;
    gameLost = false;
    gameWon = false;
    gameStarted = false;
    gamePaused = false;
    ball = new Ball();
    paddle = new Paddle();

    int k = 0;

    for (int i=3; i<8; i++) {
        for (int j=0; j<6; j++) {
          bricks[k] = new Brick(j*50, i*10);
          k++;
        }
    }
}

Arkanoid::~Arkanoid()
{
    delete ball;
    delete paddle;

    for (int i=0; i< BRICKS_COUNT; i++) {
        delete bricks[i];
    }
}

void Arkanoid::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    QPainter painter(this);

    if (gameLost) {
        finishGame(&painter, "GameOver");
    } else if (gameWon) {
        finishGame(&painter, "Game Won");
    }
    else {
        drawObjects(&painter);
    }
}

void Arkanoid::finishGame(QPainter *painter, QString message)
{
    QString textScore("Score: ");
    textScore.append(QString::number(score));

    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);
    int textWidth1 = fm.horizontalAdvance(message);
    int textWidth2 = fm.horizontalAdvance(textScore);
    int textHeight = fm.height();

    painter->setFont(font);
    int h = height();
    int w = width();

    painter->translate(QPoint(w/2, h/2));
    painter->drawText(-textWidth1/2, 0, message);
    painter->drawText(-textWidth2/2, textHeight + 2, textScore);
}

void Arkanoid::drawObjects(QPainter *painter)
{
    painter->setBrush(QBrush("red"));
    painter->drawEllipse(ball->getRect());

    painter->setBrush(QBrush("grey"));
    painter->drawRect(paddle->getRect());

    for (int i=0; i < BRICKS_COUNT; i++) {
        if (!bricks[i]->isBroken()) {
            if (i % 5 == 0) {
                painter->setBrush(QBrush("orange"));
            }
            else if (i % 5 == 1) {
                painter->setBrush(QBrush("blue"));
            }
            else if (i % 5 == 2) {
                painter->setBrush(QBrush("yellow"));
            }
            else if (i % 5 == 3) {
                painter->setBrush(QBrush("#a5f219"));
            }
            else {
                painter->setBrush(QBrush("green"));
            }
            painter->drawRect(bricks[i]->getRect());
        }
    }
}

void Arkanoid::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e);

    moveObjects();
    checkCollision();
    repaint();
}

void Arkanoid::moveObjects()
{
    ball->move();
    paddle->move();
}

void Arkanoid::keyReleaseEvent(QKeyEvent *e)
{
    Q_UNUSED(e);

    int x = 0;
    paddle->set_xDir(x);
}

void Arkanoid::keyPressEvent(QKeyEvent *e)
{
    int x = 0;

    switch (e->key()) {
        case Qt::Key_Left:
            if (paddle->getRect().left() > 0) {
                x = -1;
            }
            paddle->set_xDir(x);
            break;

        case Qt::Key_Right:
            if (paddle->getRect().right() < 300) {
                x = 1;
            }
            paddle->set_xDir(x);
            break;

        case Qt::Key_P:
            pauseGame();
            break;

        case Qt::Key_Space:
            startGame();
            break;

        case Qt::Key_Escape:
            qApp->exit();
            break;

        default:
            QWidget::keyPressEvent(e);
    }
}

void Arkanoid::startGame()
{
    if (!gameStarted) {
        ball->returnToDefault();
        paddle->returnToDefault();

        for (int i=0; i<BRICKS_COUNT; i++) {
            bricks[i]->setBroken(false);
        }

        gameLost = false;
        gameWon = false;
        gameStarted = true;
        score = 0;
        fails = 0;
        timerId = startTimer(SPEED);
    }
}

void Arkanoid::resetLocation()
{
    if (gameStarted && !gameLost) {
        ball->returnToDefault();
        paddle->returnToDefault();
    }
}

void Arkanoid::pauseGame()
{
    if (gamePaused) {
        timerId = startTimer(SPEED);
        gamePaused = false;
    } else {
        gamePaused = true;
        killTimer(timerId);
    }
}

void Arkanoid::stopGame()
{
    if (fails < 2) {
        fails++;
        resetLocation();
    }
    else {
        killTimer(timerId);
        gameLost = true;
        gameStarted = false;
    }
}

void Arkanoid::winGame()
{
    killTimer(timerId);
    gameWon = true;
    gameStarted = false;
}

void Arkanoid::resetGame()
{
    if (fails < 2) {
        killTimer(timerId);
    }
    gameStarted = false;
    startGame();
}

void Arkanoid::aboutProg()
{
    aboutGame->show();
}

void Arkanoid::checkCollision()
{
    if (ball->getRect().bottom() > 400) {
        stopGame();
    }

    int count = 0;

    for (int i=0; i < BRICKS_COUNT; i++) {
        if (bricks[i]->isBroken()) {
            count++;
        }
        else {
            break;
        }
    }

    if (count == BRICKS_COUNT) {
        winGame();
    }

    if ((ball->getRect()).intersects(paddle->getRect())) {
        int paddleLPos = paddle->getRect().left();
        int ballLPos = ball->getRect().left();

        int first = paddleLPos + 8;
        int second = paddleLPos + 16;
        int third = paddleLPos + 24;
        int fourth = paddleLPos + 32;

        if (ballLPos < first) {
            ball->set_xDir(-1);
            ball->set_yDir(-1);
        }

        if (ballLPos >= first && ballLPos < second) {
            ball->set_xDir(-1);
            ball->set_yDir(-1*ball->get_yDir());
        }

        if (ballLPos >= second && ballLPos < third) {
            ball->set_xDir(0);
            ball->set_yDir(-1);
        }

        if (ballLPos >= third && ballLPos < fourth) {
            ball->set_xDir(1);
            ball->set_yDir(-1*ball->get_yDir());
        }

        if (ballLPos > fourth) {
            ball->set_xDir(1);
            ball->set_yDir(-1);
        }
    }

    for (int i=0; i < BRICKS_COUNT; i++) {
        int ballLeft = ball->getRect().left();
        int ballHeight = ball->getRect().height();
        int ballWidth = ball->getRect().width();
        int ballTop = ball->getRect().top();

        QPoint pointRight(ballLeft + ballWidth + 1, ballTop);
        QPoint pointLeft(ballLeft - 1, ballTop);
        QPoint pointTop(ballLeft, ballTop -1);
        QPoint pointBottom(ballLeft, ballTop + ballHeight + 1);

        if ((ball->getRect()).intersects(bricks[i]->getRect())) {
            if (!bricks[i]->isBroken()) {
                if(bricks[i]->getRect().contains(pointRight)) {
                    ball->set_xDir(-1);
                }

                else if(bricks[i]->getRect().contains(pointLeft)) {
                    ball->set_xDir(1);
                }

                if(bricks[i]->getRect().contains(pointTop)) {
                    ball->set_yDir(1);
                }

                else if(bricks[i]->getRect().contains(pointBottom)) {
                    ball->set_yDir(-1);
                }

                bricks[i]->setBroken(true);
                score++;
            }
        }
    }
}
