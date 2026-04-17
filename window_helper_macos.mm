#import "window_helper_macos.h"
#import <QWidget>

#ifdef Q_OS_MAC

#import <AppKit/AppKit.h>
#import <CoreGraphics/CGWindowLevel.h>

void MacOSWindowHelper::setupAlwaysOnTopForFullscreen(QWidget *widget)
{
    if (!widget) return;

    // Get the native NSView and NSWindow
    NSView *nativeView = (NSView *)widget->winId();
    NSWindow *nativeWindow = [nativeView window];

    if (nativeWindow) {
        // Set window level to be above everything, including fullscreen apps
        [nativeWindow setLevel:NSScreenSaverWindowLevel - 1];

        // Allow window to appear on all spaces (including fullscreen spaces)
        [nativeWindow setCollectionBehavior:NSWindowCollectionBehaviorCanJoinAllSpaces |
                                        NSWindowCollectionBehaviorFullScreenAuxiliary |
                                        NSWindowCollectionBehaviorStationary];

        // Make it a floating panel that won't steal focus
        [nativeWindow setHidesOnDeactivate:NO];
        // Note: setFloatingPanel is deprecated, but we keep it for compatibility
        // The key is setting the proper window level and collection behavior

        // Ensure it stays above dock and menu bar
        [nativeWindow setLevel:CGWindowLevelForKey(kCGFloatingWindowLevelKey)];
    }
}

#endif // Q_OS_MAC
