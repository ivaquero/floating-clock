#include "window_helper_linux.h"

#ifdef Q_OS_LINUX

#include <QWidget>
#include <QGuiApplication>
#include <qpa/qplatformnativeinterface.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/extensions/Xfixes.h>

void WindowHelperLinux::setupAlwaysOnTopForFullscreen(QWidget *widget)
{
    if (!widget)
        return;

    // Get X11 display from Qt platform interface
    QNativeInterface::QX11Application *x11App = qApp->nativeInterface<QNativeInterface::QX11Application>();
    if (!x11App)
        return;

    Display *display = x11App->display();
    if (!display)
        return;

    WId windowId = widget->winId();
    if (!windowId)
        return;

    // Set window type to utility (similar to macOS panel)
    Atom windowType = XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
    Atom windowTypeUtility = XInternAtom(display, "_NET_WM_WINDOW_TYPE_UTILITY", False);
    XChangeProperty(display, windowId, windowType, XA_ATOM, 32,
                    PropModeReplace, (unsigned char *)&windowTypeUtility, 1);

    // Set window state to above
    Atom windowState = XInternAtom(display, "_NET_WM_STATE", False);
    Atom windowStateAbove = XInternAtom(display, "_NET_WM_STATE_ABOVE", False);
    XChangeProperty(display, windowId, windowState, XA_ATOM, 32,
                    PropModeReplace, (unsigned char *)&windowStateAbove, 1);

    // Set window state to skip taskbar
    Atom windowStateSkipTaskbar = XInternAtom(display, "_NET_WM_STATE_SKIP_TASKBAR", False);
    XChangeProperty(display, windowId, windowState, XA_ATOM, 32,
                    PropModeReplace, (unsigned char *)&windowStateSkipTaskbar, 1);

    // Set window state to skip pager
    Atom windowStateSkipPager = XInternAtom(display, "_NET_WM_STATE_SKIP_PAGER", False);
    XChangeProperty(display, windowId, windowState, XA_ATOM, 32,
                    PropModeReplace, (unsigned char *)&windowStateSkipPager, 1);

    // Set window state to sticky (appear on all workspaces)
    Atom windowStateSticky = XInternAtom(display, "_NET_WM_STATE_STICKY", False);
    XChangeProperty(display, windowId, windowState, XA_ATOM, 32,
                    PropModeReplace, (unsigned char *)&windowStateSticky, 1);
}

void WindowHelperLinux::setWindowAlwaysOnTop(QWidget *widget, bool alwaysOnTop)
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

void WindowHelperLinux::setWindowClickThrough(QWidget *widget, bool clickThrough)
{
    if (!widget)
        return;

    // Get X11 display from Qt platform interface
    QNativeInterface::QX11Application *x11App = qApp->nativeInterface<QNativeInterface::QX11Application>();
    if (!x11App)
        return;

    Display *display = x11App->display();
    if (!display)
        return;

    WId windowId = widget->winId();
    if (!windowId)
        return;

    if (clickThrough)
    {
        // Set window input shape to empty region
        XRectangle rect = {0, 0, 0, 0};
        XFixesSetWindowShapeRegion(display, windowId, ShapeInput, 0, 0, None);
        XFixesSetWindowShapeRegion(display, windowId, ShapeInput, 0, 0,
                                   XFixesCreateRegion(display, &rect, 1));
    }
    else
    {
        // Reset window input shape
        XFixesSetWindowShapeRegion(display, windowId, ShapeInput, 0, 0, None);
    }
}

void WindowHelperLinux::setupLinux(QWidget *widget)
{
    setupAlwaysOnTopForFullscreen(widget);
}

#endif // Q_OS_LINUX
