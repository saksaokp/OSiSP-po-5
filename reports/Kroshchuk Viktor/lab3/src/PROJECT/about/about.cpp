#include "about.h"
#include <QMessageBox>

void about()
{
    QMessageBox msgBox;
    msgBox.setText("Программу сделал студент группы ПО-5 Крощук Виктор\nДанная программа - Игра Lines");
    msgBox.exec();
}
