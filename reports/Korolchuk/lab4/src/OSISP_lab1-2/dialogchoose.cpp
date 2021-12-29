#include "dialogchoose.h"
#include <QRadioButton>
#include <QVBoxLayout>
#include <QPushButton>

dialogChoose::dialogChoose(QWidget* parent)
    :QDialog(parent)
{
    QVBoxLayout* radioLayout = new QVBoxLayout();
    QVBoxLayout* layout = new QVBoxLayout(this);

    QPushButton* startGame = new QPushButton("Начать игру");

    connect(startGame, SIGNAL(clicked()), this, SLOT(startGameClicked()));

    QList<QRadioButton*> radioButtons;
    radioButtons.reserve(Helper_class::levelsCount);

    for (int i = 0; i < Helper_class::levelsCount; ++i) {
        radioButtons << new QRadioButton(QString::number(i+1));
    }

    radioButtons[0]->setChecked(true);

    for (int i = 0; i < Helper_class::levelsCount; ++i) {
        connect(radioButtons[i], SIGNAL(toggled(bool)), this, SLOT(slotRadioToggled(bool)));
        radioLayout->addWidget(radioButtons[i]);
    }

    layout->addLayout(radioLayout);
    layout->addWidget(startGame);

    setLayout(layout);
}

void dialogChoose::startGameClicked() {
    this->close();
}

void dialogChoose::slotRadioToggled(bool value) {
    if (!value) return;
    QRadioButton * rb = qobject_cast<QRadioButton*>(sender());
    if (!rb) return;
    lvl = rb->text().toInt();
}
