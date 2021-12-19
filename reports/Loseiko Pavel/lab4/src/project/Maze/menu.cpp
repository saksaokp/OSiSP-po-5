#include "maze.h"
#include "ui_maze.h"

void Maze::SetPlugins()
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

void Maze::Set_interfase_plugins()
{
    QDir dir(qApp->applicationDirPath());
    dir.cd("themes_interfases");
    QStringList filter_1;
    filter_1 << "*.dll";
    QPluginLoader loader_1;
    foreach(QFileInfo info, dir.entryInfoList(filter_1)) {
        loader_1.setFileName(info.absoluteFilePath());
        Interface_theme* mode1 = qobject_cast<Interface_theme*>(loader_1.instance());
        if(mode1) {
            this->mTheme.push_back(mode1);
            QString name1 = loader_1.metaData().value("MetaData").toObject().value("interfas_name").toString();
            ui->modeMenu_2->addItem(name1);
            connect(ui->modeMenu_2, SIGNAL(activated(int)), this, SLOT(applyPlugin_theme(int)));
        }
        else qDebug() << "ggfdgdf";
    }
}

void Maze::applyPlugin(int index)
{
    QFont palette = this->mPlugins[index]->changeView();
    QApplication::setFont(palette);
}

void Maze::applyPlugin_theme(int index)
{
    QPalette theme = this->mTheme[index]->changeInterfase();
    QApplication::setPalette(theme);
}

void Maze::on_btn_exit_clicked()
{
    exit(0);
}

void Maze::on_btn_update_clicked()
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

void Maze::aboutQt()
{
    typedef void (*about)();
    QLibrary *aboutLib = new QLibrary("about");
    about showWindowAboutProgramm = (about)aboutLib->resolve("about");
    showWindowAboutProgramm();
    delete aboutLib;
}

Maze::~Maze(){
    delete ui;
}
