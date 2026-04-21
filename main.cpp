#include <QApplication>
#include "clock_widget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setApplicationName("Clouck");
    app.setOrganizationName("Clouck");
    app.setApplicationDisplayName("Clouck");

    ClockWidget clock;
    clock.show();

    return app.exec();
}
