#include <QApplication>
#include "FloatingClock.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    FloatingClock clock;
    clock.show();

    return app.exec();
}
