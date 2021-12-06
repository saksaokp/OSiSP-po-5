#include <QPainter>
#include <time.h>
#include <QTimer>
#include <QString>
#include <QtWidgets>
#include <QMessageBox>
#include "snake.h"
#include "ui_snake.h"

typedef void (*about)();
typedef bool (*GenerateWall)(int level, int i, int j);
typedef int (*countLevel)();

void MainWindow::SetPlugins()
{
    QDir *dir;
        #ifdef QT_DEBUG
            dir = new QDir("/home/eve9te/bstu/osisp2.0/Snake/plugins/debug");
        #else
            #ifdef QT_RELEASE
               dir = new QDir("/home/eve9te/bstu/osisp2.0/Snake/plugins/release");
            #endif
        #endif
        if(dir->entryList(QDir::Files).isEmpty())
            qDebug() << "dir isEmpty";

        foreach(QString str, dir->entryList(QDir::Files))
        {
            QPluginLoader loader(dir->absoluteFilePath(str));
            QObject *object = qobject_cast<QObject*>(loader.instance());//извлекаем плагин
            Interface *plugin = qobject_cast<Interface*>(object);//приводим к интерфейсу игры

            if(plugin)
            {
                this->mPlugins.push_back(plugin);
//                const char * namePlugin = plugin->pluginName().toLocal8Bit().data();
//                QAction *applyPlugin = new QAction(tr(namePlugin), this);
                modeMenu->addItem(plugin->pluginName());
                connect(modeMenu, SIGNAL(activated(int)), this, SLOT(applyPlugin(int)));
            }
            else
            {
                qDebug() << "error";
            }
        }
        delete dir;
}

void MainWindow::applyPlugin(int index)
{
    QFont palette = this->mPlugins[index]->changeView();
    QApplication::setFont(palette);
}

void MainWindow::InitMenu()
{
    dlg.setWindowTitle(tr("Выбирите уровень"));
    dlg.setFixedSize(QSize(MARGIN*7+(AREA_COL+1)*BLOCK_SIZE,MARGIN*2+AREA_ROW*BLOCK_SIZE));
    dlg.setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            dlg.size(),
            QApplication::desktop()->availableGeometry(this)
        )
    );
    QBoxLayout* layout = new QVBoxLayout;

    layout->setAlignment(Qt::AlignVCenter);
    QMenuBar* menuBar = new QMenuBar();
    QMenu* menu = new QMenu("О программе");
    menuBar->addMenu(menu);
    menu->addAction("about.dll", this,SLOT(aboutQt()),
                    Qt::CTRL + Qt::Key_Q);
    layout->setMenuBar(menuBar);
    QPushButton* btn_easy = new QPushButton("Easy");
    QPushButton* btn_medium = new QPushButton("Medium");
    QPushButton* btn_hard = new QPushButton("Hard");
    QPushButton* btn_update = new QPushButton("Update");
    btn_update->setContentsMargins(QMargins(0,30,0,0));
    QPushButton* btn_exit = new QPushButton("Exit");
//    btn_exit->setStyleSheet("margin-top: 5px;"
//                            "padding-top: 3px; padding-bottom: 3px;");
    connect(btn_easy, SIGNAL(clicked()), this, SLOT(BtnDlgClick1()));
    connect(btn_medium, SIGNAL(clicked()), this, SLOT(BtnDlgClick2()));
    connect(btn_hard, SIGNAL(clicked()), this, SLOT(BtnDlgClick3()));
    connect(btn_update, SIGNAL(clicked()), this, SLOT(CheckUpdate()));
    connect(btn_exit, SIGNAL(clicked()), &dlg, SLOT(close()));
    layout->addWidget(btn_easy);
    layout->addWidget(btn_medium);
    layout->addWidget(btn_hard);
    layout->addWidget(btn_update);
    layout->addWidget(btn_exit);
    layout->addWidget(modeMenu);
    dlg.setLayout(layout);
    if(dlg.exec() == QDialog::Accepted) {
        InitGame();
    }
    else
    {
        exit(0);
    }
}

void MainWindow::BtnDlgClick1()
{
    level = 1;
    LoadingLevel();
}
void MainWindow::BtnDlgClick2()
{
    level = 2;
    LoadingLevel();
}
void MainWindow::BtnDlgClick3()
{
    level = 3;
    LoadingLevel();
}
void MainWindow::LoadingLevel()
{

    QLibrary *helperLib = new QLibrary("helper");
    if (!helperLib->load())
        qDebug() << helperLib->errorString();
    if (helperLib->load())
        qDebug() << "library loaded";
    countLevel countLevel_ = (countLevel) helperLib->resolve("countLevel");
    if(level > countLevel_())
    {
        QMessageBox msgBox;
                msgBox.setWindowTitle("Error");
                msgBox.setText("Уровень еще не добавлен");
                msgBox.exec();
                return;
    }
    GenerateWall generateWall_ = (GenerateWall)helperLib->resolve("GenerateWall");
    for (int i = 0; i < AREA_COL; ++i) {
        for (int j = 0; j < AREA_ROW; ++j) {
            if(generateWall_(level, i, j)){
                wall.push_back(QPoint(i, j));
            }
        }
    }
    delete helperLib;
    dlg.accept();
}

void MainWindow::CheckUpdate()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Update");
    msgBox.setText("This is latest version");
    msgBox.exec();
}
void MainWindow::aboutQt()
{
    QLibrary *aboutLib = new QLibrary("about");
        if (!aboutLib->load())
            qDebug() << aboutLib->errorString();
        if (aboutLib->load())
            qDebug() << "library loaded";
        about showWindowAboutProgramm = (about)aboutLib->resolve("about");
        showWindowAboutProgramm();
        delete aboutLib;
}



MainWindow::~MainWindow()
{
    delete ui;
}
