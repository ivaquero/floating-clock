#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QSize>
#include <QPoint>
#include "config_manager.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    ConfigManager configManager;

    // Set some test values
    configManager.setWindowPosition(QPoint(100, 200));
    configManager.setWindowSize(QSize(300, 400));

    // Save to file
    if (configManager.saveSettings("test_config.xml"))
    {
        qDebug() << "Config saved successfully";

        // Read the file content
        QFile file("test_config.xml");
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QString content = file.readAll();
            qDebug() << "File content:";
            qDebug() << content;
            file.close();
        }
    }
    else
    {
        qDebug() << "Failed to save config";
    }

    return 0;
}
