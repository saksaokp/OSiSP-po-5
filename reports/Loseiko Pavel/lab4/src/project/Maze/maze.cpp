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
            Data.clear();
            QStringList find_filter;

            bool ok = dir_client.exists();
            if (ok) {
                dir_client.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
                dir_client.setSorting(QDir::Name);
                QFileInfoList list = dir_client.entryInfoList();

                for (int i = 0; i < list.size(); ++i) {
                    QFileInfo fileInfo = list.at(i);
                    find_filter.append(fileInfo.fileName());
                }
                qDebug() << find_filter << endl;
            }
            foreach (const QString &str, find_filter) {
                Data.append(str);
                if(&str != find_filter.last()) {
                    Data.append(" ");
                }
            }
            qDebug() << Data << endl;


            socket->write(Data);
            socket->waitForBytesWritten(100);
        }
        else {
            QStringList rec_data_update;
            QString new_version;

            rec_data_update.append(QString(Data).split(" "));
            new_version.append(rec_data_update.last());

            QDir new_client_version(qApp->applicationDirPath());
            QStringList filter;
            filter << "*.json";
            foreach(QFileInfo info, new_client_version.entryInfoList(filter)) {
                filter.clear();
                filter << info.absoluteFilePath();
            }

            QFile file(filter.back());
            if (!file.open(QIODevice::WriteOnly))
                return;
            file.write(new_version.toStdString().data());

            for(int i = 1; i < rec_data_update.size()-1; i++) {
                QFile::copy(rec_data_update.front()+'/'+rec_data_update[i], dir_client.path()+'/'+rec_data_update[i]);
            }
            mTheme.clear();
            ui->modeMenu_2->clear();
            Set_interfase_plugins();

            QMessageBox::information(this, "Информация", "Обновление завершено!");

            //create log

            QDir write_log(QDir::currentPath() + "/logs");
            QStringList formatFile;
            formatFile << "*.txt";
            foreach(QFileInfo info, write_log.entryInfoList(formatFile)) {
                formatFile.clear();
                formatFile << info.absoluteFilePath();
            }

            QFile log(formatFile.front());
            if (!log.open(QIODevice::WriteOnly))
                return;
            QString text = "Update Modules and version "+ rec_data_update.back();
            log.write(text.toStdString().data());
        }
    }
}
void Maze::on_btn_start_clicked()
{
    ui->centralwidget->setVisible(false);
    flag_game = true;
    InitGame();
}
