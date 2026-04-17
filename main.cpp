#include <QApplication>
#include "clock_widget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setApplicationName("QFlock");
    app.setOrganizationName("QFlock");
    app.setApplicationDisplayName("QFlock");

    ClockWidget clock;
    clock.show();

    return app.exec();
}
