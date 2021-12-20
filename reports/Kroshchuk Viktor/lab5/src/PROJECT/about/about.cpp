#include "about.h"
#include <QMessageBox>

void about()
{
    QMessageBox msgBox;
    msgBox.setText("Программу сделала студентка группы ПО-5 Нерода Александра\nПрограмма является MP3 плеером");
    msgBox.exec();
}
