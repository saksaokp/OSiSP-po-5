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


void Maze::applyPlugin(int index)
{
    QFont palette = this->mPlugins[index]->changeView();
    QApplication::setFont(palette);
}

void Maze::on_btn_exit_clicked()
{
    exit(0);
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
