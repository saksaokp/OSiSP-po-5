#include "Sudoku.h"
#include "ui_Sudoku.h"

#include <QActionGroup>
#include <QDir>
#include <QPluginLoader>
#include <fontPluginInterface.h>
#include <QMessageBox>
#include "Board.h"
#include <QPalette>
#include <QLibrary>
#include <QJsonDocument>
#include <QTimer>
#include <QtConcurrent/QtConcurrent>

Sudoku::Sudoku(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Sudoku) {
    ui->setupUi(this);

    QPalette pal = ui->centralWidget->palette();

    // set background
    /*pal.setColor(QPalette::Window, Qt::red);
    ui->centralWidget->setAutoFillBackground(true);
    ui->centralWidget->setPalette(pal); */

    QActionGroup* group = new QActionGroup(this);
    group->setExclusive(true);
    group->addAction(ui->actionEasy);
    group->addAction(ui->actionMedium);
    group->addAction(ui->actionHard);

    QObject::connect(ui->actionNew, SIGNAL(triggered()), ui->board, SLOT(renew()));
    QObject::connect(ui->actionClean, SIGNAL(triggered()), ui->board, SLOT(clear()));
    QObject::connect(ui->actionExit, SIGNAL(triggered()), qApp, SLOT(quit()));
    QObject::connect(group, SIGNAL(triggered(QAction*)), this, SLOT(changeMode(QAction*)));
    QObject::connect(ui->board, SIGNAL(completed(double)), this, SLOT(showProgress(double)));
    QObject::connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about()));

    loadPlugins();


    QFile settingsFile(qApp->applicationDirPath() + "/settings.json");
    settingsFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray updatesFileData = settingsFile.readAll();
    settingsFile.close();

    QJsonDocument settings = QJsonDocument::fromJson(updatesFileData);
    currentVersion = settings.object().value("version").toString();
    autoUpdateSetting = settings.object().value("autoUpdate").toBool();

    QAction *actionUpdate = ui->update->addAction(tr("Update"));
    connect(actionUpdate,  &QAction::triggered, this, [this]{ update(false); });

    if (autoUpdateSetting)
    {
        QTimer::singleShot(10000, this, [this]{ update(true); });
    }

    actionAutoUpdate = ui->update->addAction(getAutoUpdateMessage());
    connect(actionAutoUpdate, SIGNAL(triggered()), this, SLOT(setAutoUpdate()));


    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(sockReady()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(sockDisc()));


  //  this->showProgress(0);

    this->adjustSize();
    this->setFixedSize(this->size());

}

Sudoku::~Sudoku() {
    delete ui;
}

void Sudoku::changeMode(QAction* action) {
    DefaultBoards::Mode mode;

    if (action == ui->actionEasy)
        mode = DefaultBoards::Easy;
    else if (action == ui->actionMedium)
        mode = DefaultBoards::Medium;
    else if (action == ui->actionHard)
        mode = DefaultBoards::Hard;
    else {
        Q_UNREACHABLE();
        qApp->exit();
    }

    ui->board->setMode(mode);
}

void Sudoku::about()
{
    if (showAboutWindow == nullptr)
    {
        QLibrary aboutLib("D:/Programming/Qt/projects/build-about-Desktop_Qt_6_2_1_MinGW_64_bit-Debug/debug/about.dll");
        showAboutWindow = (AboutFunction)aboutLib.resolve("showAboutWindow");
    }

    showAboutWindow(this);
}

 void Sudoku::showProgress(double progress) {
    ui->statusBar->showMessage(QString("Прогресс: %1%").arg(QString::number(progress, 'f', 2)));
}


void Sudoku::changeAppFont(QFont font)
{
    QApplication::setFont(font);
}

void Sudoku::loadPlugins()
{
    QDir dir(qApp->applicationDirPath() + "/plugins");
    QStringList filter("*.dll");
    QPluginLoader loader;

    foreach(QFileInfo info, dir.entryInfoList(filter))
    {
        loader.setFileName(info.absoluteFilePath());
        FontPluginInterface* fontPlugin = qobject_cast<FontPluginInterface*>(loader.instance());

        if(fontPlugin)
        {
            QString name = loader.metaData().value("MetaData").toObject().value("fontName").toString();
            QAction* actionFontPlugin = ui->plugins->addAction(name);
            connect(actionFontPlugin, &QAction::triggered, this, [this, fontPlugin]{changeAppFont(fontPlugin->getFont());});

        }
    }
}



void Sudoku::update(bool isAutoUpdate)
{
    this->isAutoUpdate = isAutoUpdate;

    socket->connectToHost("127.0.0.1", 5555);

    socket->write(currentVersion.toStdString().c_str());

    this->isAutoUpdate = isAutoUpdate;
}

void Sudoku::sockDisc()
{
    socket->deleteLater();
}


void Sudoku::sockReady()
{
    QFuture<void> future = QtConcurrent::run([=]()
    {
        QByteArray data = socket->readAll();

        if (data == "Up-to-date" && !isAutoUpdate)
        {
            messageBoxText = "Already up-to-date";

            return;
        }

        if (data == "Up-to-date")
        {
            return;
        }

        QStringList changes = QString::fromLatin1(data).split("\n\n\n");

        for (int i = 1; i < changes.size(); i++)
        {
            QFile file(qApp->applicationDirPath() + changes[i]);
            file.open(QIODevice::WriteOnly | QIODevice::Truncate);
            file.write(changes[++i].toLatin1());
            file.close();
        }

        currentVersion = changes[0];

        writeSettingsToFile();

        messageBoxText = "Restart application";
    });

    future.waitForFinished();

    if (messageBoxText.length() != 0)
    {
        QMessageBox::information(this, "Update", messageBoxText);
    }
}

void Sudoku::setAutoUpdate()
{
    autoUpdateSetting = !autoUpdateSetting;

    actionAutoUpdate->setText(getAutoUpdateMessage());

    writeSettingsToFile();
}

void Sudoku::writeSettingsToFile()
{
    QFile settingsFile(qApp->applicationDirPath() + "/settings.json");
    settingsFile.open(QIODevice::WriteOnly | QIODevice::Text);

    QJsonObject version;
    version.insert("version", currentVersion);
    version.insert("autoUpdate", autoUpdateSetting);
    QJsonDocument settings(version);

    settingsFile.write(settings.toJson());
    settingsFile.close();
}

QString Sudoku::getAutoUpdateMessage()
{
    return autoUpdateSetting ? "Turn off auto update" : "Turn on auto update";
}

