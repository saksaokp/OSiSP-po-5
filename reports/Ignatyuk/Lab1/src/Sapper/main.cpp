#include <QApplication>

#include "sapper.hpp"

int main(int argc, char *argv[]) {
  QApplication v_App(argc, argv);

  Sapper v_Sapper;
  v_Sapper.show();

  return v_App.exec();
}
