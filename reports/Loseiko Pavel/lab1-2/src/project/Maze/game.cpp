#include "maze.h"
#include "ui_maze.h"

void Maze::InitGame()
{
    field = generate(30, 30);
    game_win->setupUi(this);
    game_win->centralwidget->setVisible(false);

    this->setWindowTitle("Maze");

    man.clear();
    wall.clear();
    gener();
    srand(time(0));
    isPause=false;
}

void Maze::gener() {
    for (int i = 0; i < field.size(); i++) {
        for (int j = 0; j < field.at(i).size(); j++) {
            int cur = field.at(i).at(j);
            if (cur == 0) {qMakePair(i, j); wall.push_back(QPoint(i, j));}
            if (cur == 4) {qMakePair(i, j); place_finish_x = i, place_finish_y = j; qDebug() << place_finish_x << place_finish_y;}
            else if (cur == 3) {qMakePair(i, j); man.push_back(QPoint(i, j));}
        }
    }
}

void Maze::paintEvent(QPaintEvent *event)
{
    if(flag_game) {
        Q_UNUSED(event);
        QPainter painter(this);
        painter.setBrush(Qt::black);
        painter.drawRect(MARGIN,MARGIN,AREA_COL*BLOCK_SIZE,AREA_ROW*BLOCK_SIZE);
        painter.setBrush(Qt::blue);
        for(int i=0;i<wall.size();i++)
            painter.drawRect(MARGIN+wall[i].x()*BLOCK_SIZE,MARGIN+wall[i].y()*BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE);

        painter.setBrush(Qt::red);
        painter.drawRect(MARGIN+man[0].x()*BLOCK_SIZE,MARGIN+man[0].y()*BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE);
    }
}

void Maze::keyPressEvent(QKeyEvent *event)
{
    if(flag_game) {

        switch(event->key())
        {
        case Qt::Key_Up:
                SnakeUpdate(Qt::Key_Up);
            break;
        case Qt::Key_Down:
                SnakeUpdate(Qt::Key_Down);
            break;
        case Qt::Key_Left:
                SnakeUpdate(Qt::Key_Left);
            break;
        case Qt::Key_Right:
                SnakeUpdate(Qt::Key_Right);
            break;
        case Qt::Key_Escape:
            PauseResumeGame();
            break;
        default:
            break;
        }
    }
}

bool Maze::IsGameOver()
{
    int x=man.front().x();
    int y=man.front().y();
    if(x<0||x>AREA_COL-1||y<0||y>AREA_ROW-1)
        return true;

    for(int i=0;i<wall.size();i++)
        if(wall[i]==man.front())
            return true;
    return false;
}

void Maze::SnakeUpdate(int key)
{
    if(key == Qt::Key_Up) man.push_front(QPoint(man.front().x(),man.front().y()-1));
    if(key == Qt::Key_Down) man.push_front(QPoint(man.front().x(),man.front().y()+1));
    if(key == Qt::Key_Left) man.push_front(QPoint(man.front().x()-1,man.front().y()));
    if(key == Qt::Key_Right) man.push_front(QPoint(man.front().x()+1,man.front().y()));

    if(IsGameOver())
    {
        man.clear();
        man.push_back(QPoint(place_x, place_y));
    }
    else {
        man.pop_back();
        place_x = man.front().x();
        place_y = man.front().y();
        qDebug() << place_x << place_y;
        update();
    }
    if(place_x == place_finish_x && place_y == place_finish_y) {
        QMessageBox::information(this, "Информация", "Вы прошли уровень");
        flag_game = false;
        InitMenu();
    }
}
