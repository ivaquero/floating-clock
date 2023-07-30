#include <QApplication>

#include "clock.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  Clock clock;
  return app.exec();
}
