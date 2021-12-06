#include "about.h"
#include <QMessageBox>

void about()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("About programm");
    msgBox.setText("The programm was developed by eve9te");
    msgBox.exec();
}
