#include "window_helper.h"

#ifdef Q_OS_MAC
#include "window_helper_macos.h"
#elif defined(Q_OS_WIN)
#include "window_helper_windows.h"
#elif defined(Q_OS_LINUX)
#include "window_helper_linux.h"
#endif

void WindowHelper::setupAlwaysOnTopForFullscreen(QWidget *widget)
{
    if (!widget)
        return;

#ifdef Q_OS_MAC
    setupMacOS(widget);
#elif defined(Q_OS_WIN)
    setupWindows(widget);
#elif defined(Q_OS_LINUX)
    setupLinux(widget);
#endif
}

void WindowHelper::setWindowAlwaysOnTop(QWidget *widget, bool alwaysOnTop)
{
    if (!widget)
        return;

    Qt::WindowFlags flags = widget->windowFlags();
    if (alwaysOnTop)
    {
        flags |= Qt::WindowStaysOnTopHint;
    }
    else
    {
        flags &= ~Qt::WindowStaysOnTopHint;
    }
    widget->setWindowFlags(flags);
    widget->show(); // Required to apply new flags
}

void WindowHelper::setWindowClickThrough(QWidget *widget, bool clickThrough)
{
    if (!widget)
        return;

#ifdef Q_OS_MAC
    // macOS: Make window ignore mouse events
    widget->setAttribute(Qt::WA_TransparentForMouseEvents, clickThrough);
#elif defined(Q_OS_WIN)
    // Windows: Will be implemented in Windows helper
    widget->setAttribute(Qt::WA_TransparentForMouseEvents, clickThrough);
#elif defined(Q_OS_LINUX)
    // Linux: Will be implemented in Linux helper
    widget->setAttribute(Qt::WA_TransparentForMouseEvents, clickThrough);
#endif
}

void WindowHelper::setWindowTransparent(QWidget *widget, bool transparent)
{
    if (!widget)
        return;

    if (transparent)
    {
        widget->setAttribute(Qt::WA_TranslucentBackground);
        widget->setWindowFlags(widget->windowFlags() | Qt::FramelessWindowHint);
    }
    else
    {
        widget->setAttribute(Qt::WA_TranslucentBackground, false);
    }
}

#ifdef Q_OS_MAC
void WindowHelper::setupMacOS(QWidget *widget)
{
    MacOSWindowHelper::setupAlwaysOnTopForFullscreen(widget);
}
#endif

#ifdef Q_OS_WIN
void WindowHelper::setupWindows(QWidget *widget)
{
    WindowHelperWindows::setupAlwaysOnTopForFullscreen(widget);
}
#endif

#ifdef Q_OS_LINUX
void WindowHelper::setupLinux(QWidget *widget)
{
    WindowHelperLinux::setupAlwaysOnTopForFullscreen(widget);
}
#endif
