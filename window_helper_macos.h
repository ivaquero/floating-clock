#ifndef WINDOW_HELPER_MACOS_H
#define WINDOW_HELPER_MACOS_H

class QWidget;

#ifdef __OBJC__
@class NSWindow;
#endif

class MacOSWindowHelper
{
public:
    static void setupAlwaysOnTopForFullscreen(QWidget *widget);
};

#endif // WINDOW_HELPER_MACOS_H
