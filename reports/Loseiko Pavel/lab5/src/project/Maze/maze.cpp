#include "maze.h"
#include "ui_maze.h"

Maze::Maze(QWidget *parent): QMainWindow(parent), ui(new Ui::Maze)
{
    typedef QString (*Helper_set_name_window)();
    typedef QString (*Helper_set_name_about)();
    typedef QString (*Helper_set_name_btn)();
    ui->setupUi(this);

    setFixedSize(QSize(MARGIN*2+(AREA_COL+1)*BLOCK_SIZE,MARGIN*2+AREA_ROW*BLOCK_SIZE));
    SetPlugins();
    Set_interfase_plugins();

    // установка имени окна приложения
    QLibrary *helper_set = new QLibrary("Helper");
    Helper_set_name_window set_window_name_ = (Helper_set_name_window)helper_set->resolve("set_window_name");
    QString windowTitle = set_window_name_();
    delete helper_set;
    this->setWindowTitle(windowTitle);

    // установка имени кнопки
    QLibrary *helper_set_n_btn = new QLibrary("Helper");
    Helper_set_name_btn set_btn_name_ = (Helper_set_name_btn)helper_set_n_btn->resolve("set_window_btn_name");
    ui->btn_start->setText(set_btn_name_());
    delete helper_set_n_btn;

    // установка имени About
    QLibrary *helper_set_n_about = new QLibrary("Helper");
    Helper_set_name_about set_window_name_first = (Helper_set_name_about)helper_set_n_about->resolve("set_name_About");
    QMenu* menu = new QMenu(set_window_name_first());
    delete helper_set_n_about;
    ui->menubar->addMenu(menu);
    menu->addAction("about.dll", this,SLOT(aboutQt()), Qt::CTRL + Qt::Key_Q);

}

void Maze::InitMenu() {

    typedef QString (*Helper_set_name_window)();
    typedef QString (*Helper_set_name_about)();
    typedef QString (*Helper_set_name_btn)();
    ui->setupUi(this);
    setFixedSize(QSize(MARGIN*2+(AREA_COL+1)*BLOCK_SIZE,MARGIN*2+AREA_ROW*BLOCK_SIZE));
    connect(ui->btn_start, SIGNAL(clicked()), this, SLOT(on_btn_start_clicked()));
    connect(ui->btn_update, SIGNAL(clicked()), this, SLOT(on_btn_update_clicked()));
    connect(ui->btn_exit, SIGNAL(clicked()), this, SLOT(on_btn_exit_clicked()));
    SetPlugins();
    Set_interfase_plugins();

    // установка имени окна приложения
    QLibrary *helper_set = new QLibrary("Helper");
    Helper_set_name_window set_window_name_ = (Helper_set_name_window)helper_set->resolve("set_window_name");
    QString windowTitle = set_window_name_();
    delete helper_set;
    this->setWindowTitle(windowTitle);

    // установка имени кнопки
    QLibrary *helper_set_n_btn = new QLibrary("Helper");
    Helper_set_name_btn set_btn_name_ = (Helper_set_name_btn)helper_set_n_btn->resolve("set_window_btn_name");
    ui->btn_start->setText(set_btn_name_());
    delete helper_set_n_btn;

    // установка имени About
    QLibrary *helper_set_n_about = new QLibrary("Helper");
    Helper_set_name_about set_window_name_first = (Helper_set_name_about)helper_set_n_about->resolve("set_name_About");
    QMenu* menu = new QMenu(set_window_name_first());
    delete helper_set_n_about;
    ui->menubar->addMenu(menu);
    menu->addAction("about.dll", this, SLOT(aboutQt()), Qt::CTRL + Qt::Key_Q);

}

void Maze::PauseResumeGame()
{
    if(!isPause)
    {
        isPause=!isPause;
        InitPause();
    }
    else isPause=!isPause;
}

void Maze::InitPause()
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

void Maze::sockDisc() {
    socket->disconnected();
}

void Maze::sockReady() {
    if(socket->waitForConnected(100)) {
        socket->waitForReadyRead(100);
        Data = socket->readAll();

         QDir dir_client(QDir::currentPath() + "/themes_interfases");

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
void Maze::on_btn_start_clicked()
{
    ui->centralwidget->setVisible(false);
    flag_game = true;
    InitGame();
}
