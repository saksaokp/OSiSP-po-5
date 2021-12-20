#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QComboBox>
#include "GameLogic.h"
#include <QGridLayout>
#include "cell.h"
#include "Definitions.h"
#include <QPainter>
#include <QAnimationDriver>
#include <QAnimationGroup>
#include <QGraphicsOpacityEffect>
#include <QButtonGroup>
#include <QFontDatabase>
#include <QMessageBox>
#include <QCloseEvent>
#include <QMainWindow>
#include <QPluginLoader>
#include <QLibrary>
#include <QFileDialog>
#include "interface.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    QPushButton* score;
    QString set_name_second;
    QString set_name_first;
    void gameOver();
    void startScreen();
    void startGame();
    void info();
    void setPlugins();
    void nextMove();
    QIcon mergedIcon(Ghosts type, MatrixPoint place, bool select = true);
    ~MainWindow();

public slots:
    void applyPlugin(int index);
    void ghostWasSelected(Ghosts type, MatrixPoint place);
    void ghostWasDeselected(Ghosts type, MatrixPoint place);
    void ghostWasGenerated(Ghosts type, MatrixPoint place);
    void ghostWasMoved(std::vector<Node> road, Ghosts type);
    void ghostWasDeleted(MatrixPoint place);
    void finishedAnimating();

    void playButtonWasClicked(bool zrtik);
    void aboutButtonWasClicked(bool zrtik);
    void settingsButtonWasClicked(bool zrtik);
    void homeButtonWasClicked(bool zrtik);

    void buttonWasPressed(QWidget* button);
    void buttonWasReleased(QWidget* button);

signals:
    wasPressed(QWidget* button);
    wasReleased(QPushButton* button);

private:
    QWidget* board = new QWidget();
    Cell* **cells;
    Ghosts lastCellType;
    MatrixPoint* lastCellPlace;
    void closeEvent(QCloseEvent *bar);
    Ui::MainWindow *ui;
    QComboBox *list;
    QComboBox *list_theme;
    QVector <Interface*> mPlugin;
    QVector <Interface*> mThemes;
};
#endif // MAINWINDOW_H
