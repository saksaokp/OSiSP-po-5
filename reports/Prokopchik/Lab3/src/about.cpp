#include "about.h"
#include <QMessageBox>

void showAboutWindow(QWidget* parent)
{
    QMessageBox::about(parent, "О программе", "Прокопчик Егор ПО-5. Судоку");
}
