#include "Sudoku.h"
#include <QApplication>
#include <QLibrary>

typedef QString (*SetNameWindow)();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Sudoku w;

    QLibrary *helper_set = new QLibrary("D:\\Programming\\Qt\\projects\\build-helper-Desktop_Qt_6_2_1_MinGW_64_bit-Debug\\debug\\helper.dll");
        SetNameWindow set_window_name_ = (SetNameWindow)helper_set->resolve("set_window_name");
        QString windowTitle = set_window_name_();
        delete helper_set;
        w.setWindowTitle(windowTitle);

    w.show();

    return a.exec();
}
