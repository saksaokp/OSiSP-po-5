#include "snake.h"
#include "ui_snake.h"

Snake::Snake(QWidget *parent): QMainWindow(parent), ui(new Ui::Snake)
{
    typedef QString (*Helper_set_name_window)();
    typedef QString (*Helper_set_name_about)();
    ui->setupUi(this);

    setFixedSize(QSize(MARGIN*7+(AREA_COL+1)*BLOCK_SIZE,MARGIN*2+AREA_ROW*BLOCK_SIZE));
    SetPlugins();
    Setlevels();

    // установка имени окна приложения
    QLibrary *helper_set = new QLibrary("Helper");
    Helper_set_name_window set_window_name_ = (Helper_set_name_window)helper_set->resolve("set_window_name");
    QString windowTitle = set_window_name_();
    delete helper_set;
    this->setWindowTitle(windowTitle);

    // установка имени About
    QLibrary *helper_set_n_about = new QLibrary("Helper");
    Helper_set_name_about set_window_name_first = (Helper_set_name_about)helper_set_n_about->resolve("set_name_About");
    QMenu* menu = new QMenu(set_window_name_first());
    delete helper_set_n_about;
    ui->menubar->addMenu(menu);
    menu->addAction("about.dll", this,SLOT(aboutQt()), Qt::CTRL + Qt::Key_Q);

}

void Snake::InitMenu() {

    typedef QString (*Helper_set_name_window)();
    typedef QString (*Helper_set_name_about)();
    ui->setupUi(this);
    levels.clear();
    setFixedSize(QSize(MARGIN*7+(AREA_COL+1)*BLOCK_SIZE,MARGIN*2+AREA_ROW*BLOCK_SIZE));
    connect(ui->levelslist, SIGNAL(currentIndexChanged(const QString)), this, SLOT(on_levelslist_currentIndexChanged(QString)));
    connect(ui->btn_start, SIGNAL(clicked()), this, SLOT(on_btn_start_clicked()));
    connect(ui->btn_update, SIGNAL(clicked()), this, SLOT(on_btn_update_clicked()));
    connect(ui->btn_exit, SIGNAL(clicked()), this, SLOT(on_btn_exit_clicked()));
    SetPlugins();
    Setlevels();

    // установка имени окна приложения
    QLibrary *helper_set = new QLibrary("Helper");
    Helper_set_name_window set_window_name_ = (Helper_set_name_window)helper_set->resolve("set_window_name");
    QString windowTitle = set_window_name_();
    delete helper_set;
    this->setWindowTitle(windowTitle);

    // установка имени About
    QLibrary *helper_set_n_about = new QLibrary("Helper");
    Helper_set_name_about set_window_name_first = (Helper_set_name_about)helper_set_n_about->resolve("set_name_About");
    QMenu* menu = new QMenu(set_window_name_first());
    delete helper_set_n_about;
    ui->menubar->addMenu(menu);
    menu->addAction("about.dll", this, SLOT(aboutQt()), Qt::CTRL + Qt::Key_Q);

}

void Snake::PauseResumeGame()
{
    if(!isPause)
    {
        isPause=!isPause;
        gameTimer->stop();
        InitPause();
    }
    else
    {
        isPause=!isPause;
        gameTimer->start(TIME_INTERVAL);
    }
}

void Snake::InitPause()
{
    QMessageBox::StandardButton pause;
      pause = QMessageBox::question(this, "Pause", "Продолжить?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (pause == QMessageBox::Yes) {
        PauseResumeGame();
      }
      else {
          flag_game = false;
          InitMenu();

      }
}

void Snake::GameOver()
{
    gameTimer->stop();


    snake.pop_front();

    QMessageBox::StandardButton toMain;
    toMain = QMessageBox::question(this,"Failed","Game over!", QMessageBox::Ok|QMessageBox::Ok);
    if(toMain == QMessageBox::Ok) {
        flag_game = false;
        InitMenu();
    }
}
void Snake::sockDisc() {
    socket->disconnected();
}

void Snake::sockReady() {
    if(socket->waitForConnected(100)) {
        socket->waitForReadyRead(100);
        Data = socket->readAll();

         QDir dir_client(QDir::currentPath() + "/level");

        if(Data == "Actuale") {
            QMessageBox::information(this, "Информация", "Соединение установлено\nУ вас актуальная версия программы!");
            socket->disconnected();
        }

        else if(Data == "Need update") {
            QMessageBox msg;
            msg.setText("New version is available");
            msg.setInformativeText("Do you want to update app?");
            msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            msg.setDefaultButton(QMessageBox::Yes);
            int res = msg.exec();

            //loading

            if (res == QMessageBox::Yes) {
                sockDisc();
                socket->waitForDisconnected(1);

                QThread *thread= new QThread;
                Thread *my = new Thread("B");

                my->moveToThread(thread);

                connect(my, SIGNAL(time_load(int)), this, SLOT(showProgress(int)));
                connect(my, SIGNAL(load_update(int)), this, SLOT(loading(int)));
                connect(my, SIGNAL(load_video(int)), this, SLOT(download_video(int)));

                connect(thread, SIGNAL(started()), my, SLOT(run()));

                thread->start();
            }
        }
    }
}
