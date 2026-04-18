#include "window_helper_linux.h"

#ifdef Q_OS_LINUX

#include <QtWidgets/QWidget>
#include <QtGui/QGuiApplication>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/extensions/Xfixes.h>

// X11 type definitions for compatibility
typedef XserverRegion Region;

// X11 shape constants
#define ShapeInput 2
#define ShapeBounding 0

// Qt 6.x compatibility - use only public Qt interfaces
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
    XChangeProperty(display, windowId, windowType, XA_ATOM, 32, PropModeReplace,
                    (unsigned char *)&windowTypeUtility, 1);

    // Set window state to above (always on top)
    Atom wmState = XInternAtom(display, "_NET_WM_STATE", False);
    Atom wmStateAbove = XInternAtom(display, "_NET_WM_STATE_ABOVE", False);
    XChangeProperty(display, windowId, wmState, XA_ATOM, 32, PropModeReplace,
                    (unsigned char *)&wmStateAbove, 1);

    // Set window state to sticky (appears on all desktops)
    Atom wmStateSticky = XInternAtom(display, "_NET_WM_STATE_STICKY", False);
    XChangeProperty(display, windowId, wmState, XA_ATOM, 32, PropModeAppend,
                    (unsigned char *)&wmStateSticky, 1);

    // Set window state to skip taskbar and pager
    Atom wmStateSkipTaskbar = XInternAtom(display, "_NET_WM_STATE_SKIP_TASKBAR", False);
    Atom wmStateSkipPager = XInternAtom(display, "_NET_WM_STATE_SKIP_PAGER", False);
    Atom states[] = {wmStateSkipTaskbar, wmStateSkipPager};
    XChangeProperty(display, windowId, wmState, XA_ATOM, 32, PropModeAppend,
                    (unsigned char *)states, 2);

    XFlush(display);
}

void WindowHelperLinux::setWindowAlwaysOnTop(QWidget *widget, bool alwaysOnTop)
{
    if (!widget)
        return;

    QNativeInterface::QX11Application *x11App = qApp->nativeInterface<QNativeInterface::QX11Application>();
    if (!x11App)
        return;

    Display *display = x11App->display();
    if (!display)
        return;

    WId windowId = widget->winId();
    if (!windowId)
        return;

    if (alwaysOnTop)
    {
        // Set window state to above (always on top)
        Atom wmState = XInternAtom(display, "_NET_WM_STATE", False);
        Atom wmStateAbove = XInternAtom(display, "_NET_WM_STATE_ABOVE", False);
        XChangeProperty(display, windowId, wmState, XA_ATOM, 32, PropModeReplace,
                        (unsigned char *)&wmStateAbove, 1);
    }
    else
    {
        // Remove always on top state
        Atom wmState = XInternAtom(display, "_NET_WM_STATE", False);
        Atom wmStateAbove = XInternAtom(display, "_NET_WM_STATE_ABOVE", False);
        XDeleteProperty(display, windowId, wmState);
    }

    XFlush(display);
}

void WindowHelperLinux::setWindowClickThrough(QWidget *widget, bool clickThrough)
{
    if (!widget)
        return;

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
        // Enable click-through using X11 shape extension
        XRectangle rect = {0, 0, 1, 1};
        Region region = XFixesCreateRegion(display, &rect, 1);
        XFixesSetWindowShapeRegion(display, windowId, ShapeInput, 0, 0, region);
        XFixesSetWindowShapeRegion(display, windowId, ShapeBounding, 0, 0, region);
        XFixesDestroyRegion(display, region);
    }
    else
    {
        // Disable click-through - restore normal input handling
        XRectangle rect = {0, 0, 0, 0};
        Region region = XFixesCreateRegion(display, &rect, 1);
        XFixesSetWindowShapeRegion(display, windowId, ShapeInput, 0, 0, region);
        XFixesDestroyRegion(display, region);
    }

    XFlush(display);
}

void WindowHelperLinux::setupLinux(QWidget *widget)
{
    if (!widget)
        return;

    setupAlwaysOnTopForFullscreen(widget);
}

#endif // Q_OS_LINUX
