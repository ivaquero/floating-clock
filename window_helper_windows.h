#ifndef WINDOW_HELPER_WINDOWS_H
#define WINDOW_HELPER_WINDOWS_H

#include <QWidget>

#ifdef Q_OS_WIN
#include <Windows.h>
#endif

class WindowHelperWindows
{
public:
    static void setupAlwaysOnTopForFullscreen(QWidget *widget);
    static void setWindowAlwaysOnTop(QWidget *widget, bool alwaysOnTop);
    static void setWindowClickThrough(QWidget *widget, bool clickThrough);

private:
    static void setWindowExStyle(QWidget *widget, DWORD style, bool enable);
    static HWND getWindowHandle(QWidget *widget);
};

#endif // WINDOW_HELPER_WINDOWS_H
