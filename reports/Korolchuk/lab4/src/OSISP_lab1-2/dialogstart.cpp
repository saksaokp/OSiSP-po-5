#include "dialogstart.h"
#include "dialogchoose.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QProcess>
#include <QDialog>
#include <QDir>

dialogStart::dialogStart(QWidget *parent)
    : QDialog(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    QPushButton* chooseLvl = new QPushButton("Выбрать уровень");
    QPushButton* checkUpdates = new QPushButton("Проверить обновления");

    connect(chooseLvl, SIGNAL(clicked()), this, SLOT(chooseLvlClicked()));
    connect(checkUpdates, SIGNAL(clicked()), this, SLOT(checkUpdatesClicked()));

    layout->addWidget(chooseLvl);
    layout->addWidget(checkUpdates);

    setLayout(layout);
}

void dialogStart::chooseLvlClicked() {
    dialogChoose* dialog = new dialogChoose(this);
    dialog->setModal(true);
    dialog->exec();

    lvl = dialog->lvl;
    operation = "startGame";

    this->close();
}

void dialogStart::checkUpdatesClicked() {
    QObject *parent = this;

    QString program = QDir::currentPath() + "/../updater/Updater";
    QStringList arguments;

    QProcess *myProcess = new QProcess(parent);
    myProcess->startDetached(program, arguments);

    operation = "checkUpdates";

    this->close();
}
