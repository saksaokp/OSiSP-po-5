#include "about.h"
#include <QMessageBox>

void about()
{
    QMessageBox msgBox;
    msgBox.setText("Программу сделала студентка группы ПО-5 Андросюк Мария");
    msgBox.exec();
}
