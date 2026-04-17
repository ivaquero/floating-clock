#ifndef WINDOW_HELPER_H
#define WINDOW_HELPER_H

#include <QWidget>

class WindowHelper
{
public:
    static void setupAlwaysOnTopForFullscreen(QWidget *widget);
    static void setWindowAlwaysOnTop(QWidget *widget, bool alwaysOnTop);
    static void setWindowClickThrough(QWidget *widget, bool clickThrough);
    static void setWindowTransparent(QWidget *widget, bool transparent);

private:
    // Platform-specific implementations
    static void setupMacOS(QWidget *widget);
    static void setupWindows(QWidget *widget);
    static void setupLinux(QWidget *widget);
};

#endif // WINDOW_HELPER_H
