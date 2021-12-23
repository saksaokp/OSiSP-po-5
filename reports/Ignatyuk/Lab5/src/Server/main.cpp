#include <QCoreApplication>

#include "server.hpp"

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);
  Server v_Server{};
  return a.exec();
}
