#ifndef DIALOGCHOOSE_H
#define DIALOGCHOOSE_H

#include <QWidget>
#include <QDialog>
#include "helper_class.h"

class dialogChoose : public QDialog
{
    Q_OBJECT

public:
    explicit dialogChoose(QWidget* parent = nullptr);

    int lvl;

private slots:
    void startGameClicked();
    void slotRadioToggled(bool value);
};

#endif // DIALOGCHOOSE_H
