#include "about.h"
#include <QMessageBox>

void about()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("About programm");
    msgBox.setText("Эту программу сделал Белко Владислав");
    msgBox.exec();
}
