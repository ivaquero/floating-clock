#include <QApplication>

#include "flock.h"

auto main(int argc, char *argv[]) -> int {
  QApplication app(argc, argv);

  Clock clock;
  return app.exec();
}
