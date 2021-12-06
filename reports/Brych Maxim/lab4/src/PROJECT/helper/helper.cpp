#include "helper.h"

bool GenerateSnake(int i)
{
    bool temp = false;
    if(i >= 0 && i < 3)
        temp = true;
    return temp;
}
QString set_window_name() {
    return QString("Выберите уровень");
}

QString set_name_About() {
    return QString("О программе");
}
