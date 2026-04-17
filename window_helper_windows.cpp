#include "window_helper_windows.h"

#ifdef Q_OS_WIN

#include <QWidget>
#include <QWindow>
#include <qt_windows.h>
#include <windows.h>

// Ensure we have the proper Windows version for API functions
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600 // Windows Vista and later
#endif

void WindowHelperWindows::setupAlwaysOnTopForFullscreen(QWidget *widget)
{
    if (!widget)
        return;

    HWND hwnd = getWindowHandle(widget);
    if (!hwnd)
        return;

    // Set window as topmost
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0,
                 SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

    // Make window appear on all desktops (similar to macOS spaces)
    SetWindowLongPtr(hwnd, GWL_EXSTYLE,
                     GetWindowLongPtr(hwnd, GWL_EXSTYLE) | WS_EX_TOOLWINDOW);

    // Set extended window style to stay on top in fullscreen mode
    SetWindowLongPtr(hwnd, GWL_EXSTYLE,
                     GetWindowLongPtr(hwnd, GWL_EXSTYLE) | WS_EX_TOPMOST);

    // Make window not appear in taskbar
    SetWindowLongPtr(hwnd, GWL_EXSTYLE,
                     GetWindowLongPtr(hwnd, GWL_EXSTYLE) | WS_EX_NOACTIVATE);
}

void WindowHelperWindows::setWindowAlwaysOnTop(QWidget *widget, bool alwaysOnTop)
{
    if (!widget)
        return;

    HWND hwnd = getWindowHandle(widget);
    if (!hwnd)
        return;

    SetWindowPos(hwnd, alwaysOnTop ? HWND_TOPMOST : HWND_NOTOPMOST,
                 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
}

void WindowHelperWindows::setWindowClickThrough(QWidget *widget, bool clickThrough)
{
    if (!widget)
        return;

    HWND hwnd = getWindowHandle(widget);
    if (!hwnd)
        return;

    if (clickThrough)
    {
        // Make window transparent to mouse events
        SetWindowLong(hwnd, GWL_EXSTYLE,
                      GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_TRANSPARENT);
    }
    else
    {
        // Remove transparent mouse event handling
        SetWindowLongPtr(hwnd, GWL_EXSTYLE,
                         GetWindowLongPtr(hwnd, GWL_EXSTYLE) & ~WS_EX_TRANSPARENT);
    }
}

void WindowHelperWindows::setWindowExStyle(QWidget *widget, DWORD style, bool enable)
{
    if (!widget)
        return;

    HWND hwnd = getWindowHandle(widget);
    if (!hwnd)
        return;

    DWORD currentStyle = GetWindowLongPtr(hwnd, GWL_EXSTYLE);
    if (enable)
    {
        currentStyle |= style;
    }
    else
    {
        currentStyle &= ~style;
    }
    SetWindowLongPtr(hwnd, GWL_EXSTYLE, currentStyle);
}

HWND WindowHelperWindows::getWindowHandle(QWidget *widget)
{
    if (!widget)
        return nullptr;

    QWindow *window = widget->windowHandle();
    if (!window)
    {
        // Try to get window handle from native parent
        QWidget *nativeParent = widget->nativeParentWidget();
        if (nativeParent)
        {
            window = nativeParent->windowHandle();
        }
    }

    if (window)
    {
        return reinterpret_cast<HWND>(window->winId());
    }

    return nullptr;
}

#endif // Q_OS_WIN
