#ifndef WINDOW_HELPER_LINUX_H
#define WINDOW_HELPER_LINUX_H

#include <QWidget>

class WindowHelperLinux
{
public:
    static void setupAlwaysOnTopForFullscreen(QWidget *widget);
    static void setWindowAlwaysOnTop(QWidget *widget, bool alwaysOnTop);
    static void setWindowClickThrough(QWidget *widget, bool clickThrough);
    static void setupLinux(QWidget *widget);
};

#endif // WINDOW_HELPER_LINUX_H
