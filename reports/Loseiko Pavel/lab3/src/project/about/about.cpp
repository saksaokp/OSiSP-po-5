#include "about.h"
#include <QMessageBox>

void about()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("About programm");
    msgBox.setText("Эту программу сделал Лозейко Павел");
    msgBox.exec();
}
