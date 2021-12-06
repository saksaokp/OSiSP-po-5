#include "snake.h"
#include "ui_snake.h"

void Snake::SetPlugins()
{
    QDir dir(qApp->applicationDirPath());
        dir.cd("plugins");
        QStringList filter;
        filter << "*.dll";
        QPluginLoader loader;
        foreach(QFileInfo info, dir.entryInfoList(filter)) {
            loader.setFileName(info.absoluteFilePath());
            Interface* mode = qobject_cast<Interface*>(loader.instance());
            if(mode) {
                this->mPlugins.push_back(mode);
                QString name = loader.metaData().value("MetaData").toObject().value("Mode_name").toString();
                ui->modeMenu->addItem(name);
                connect(ui->modeMenu, SIGNAL(activated(int)), this, SLOT(applyPlugin(int)));
            }
        }
}

void Snake::Setlevels()
{
    QDir dir_levels(QDir::currentPath() + "/level");

    bool ok = dir_levels.exists();
    if (ok) {
        dir_levels.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
        dir_levels.setSorting(QDir::Name);
        QFileInfoList list = dir_levels.entryInfoList();

        for (int i = 0; i < list.size(); ++i) {
            QFileInfo fileInfo = list.at(i);
            levels.append(fileInfo.fileName());
        }
        countLevels = levels.length();
        ui->colLevel->setText(QString::number(countLevels));
        foreach (const QString &str, levels) {
            ui->levelslist->addItem(str);
        }
    }
}


void Snake::applyPlugin(int index)
{
    QFont palette = this->mPlugins[index]->changeView();
    QApplication::setFont(palette);
}

void Snake::on_btn_start_clicked()
{
    wall.clear();
    typedef bool (*GenerateWall)(int i, int j);
    QLibrary *loadLevel = new QLibrary("./level/"+level);
    GenerateWall generateWall_ = (GenerateWall)loadLevel->resolve("GenerateWall");
    for (int i = 0; i < AREA_COL; ++i) {
        for (int j = 0; j < AREA_ROW; ++j) {
            if(generateWall_(i, j)){
                wall.push_back(QPoint(i, j));
            }
        }
    }
    ui->centralwidget->setVisible(false);
    flag_game = true;
    InitGame();
    delete loadLevel;
}

void Snake::on_levelslist_currentIndexChanged(const QString &arg1)
{
    level = arg1;
}

void Snake::showProgress(int i)
{
    progress = i;
    ui->statusbar->showMessage(QString::number(progress)+"%");
    ui->statusbar->showMessage("100%");
    QMessageBox::information(this, "Информация", "Обновление завершено!");
}

void Snake::loading(int res)
{
    if(res == 1) {
        levels.clear();
        ui->levelslist->clear();
        Setlevels();
    }
}

void Snake::download_video(int msg)
{
    if(msg == 1) QMessageBox::information(this, "Информация", "Видео получено!");
}

void Snake::on_btn_exit_clicked()
{
    exit(0);
}

void Snake::on_btn_update_clicked()
{
    QMessageBox msg;

    socket = new QTcpSocket();
    connect(socket,SIGNAL(readyRead()),this,SLOT(sockReady()));

    Data.clear();

    QDir client_version(qApp->applicationDirPath());
    QStringList filter;
    filter << "*.json";
    foreach(QFileInfo info, client_version.entryInfoList(filter)) {
        filter.clear();
        filter << info.absoluteFilePath();
    }
    QFile file(filter.back());
    if (!file.open(QIODevice::ReadOnly))
        return;
    Data = file.readAll();
    socket->connectToHost("127.0.0.1", 5555);
    socket->waitForConnected(1);
    if(socket->state() == QTcpSocket::ConnectedState) {
        if(socket->isOpen()) {
            socket->write(Data);

            socket->waitForBytesWritten(100);
        }
    }
    else {
        msg.setWindowTitle("Информация");
        msg.setText("Соединение не установлено");
        msg.exec();
    }
}

void Snake::aboutQt()
{
    typedef void (*about)();
    QLibrary *aboutLib = new QLibrary("about");
    about showWindowAboutProgramm = (about)aboutLib->resolve("about");
    showWindowAboutProgramm();
    delete aboutLib;
}

Snake::~Snake(){
    delete ui;
}
