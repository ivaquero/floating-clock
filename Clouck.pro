# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

TARGET = Clouck

QT = core gui widgets

SOURCES = \
   $$PWD/main.cpp \
   $$PWD/clock_widget.cpp \
   $$PWD/config_manager.cpp \
   $$PWD/window_helper.cpp

HEADERS = \
   $$PWD/clock_widget.h \
   $$PWD/config_manager.h \
   $$PWD/window_helper.h \
   $$PWD/window_helper_macos.h \
   $$PWD/window_helper_windows.h \
   $$PWD/window_helper_linux.h

macx {
   OBJECTIVE_SOURCES = $$PWD/window_helper_macos.mm
   LIBS += -framework AppKit -framework CoreGraphics
   QMAKE_CXXFLAGS += -x objective-c++
}

win32 {
   SOURCES += $$PWD/window_helper_windows.cpp
   LIBS += -luser32 -ldwmapi -luser32 -lgdi32 -lkernel32
}

unix:!macx {
   LIBS += -lX11 -lXfixes
}

INCLUDEPATH = \
    $$PWD/.

# Set build output directories
DESTDIR = $$PWD/build
OBJECTS_DIR = $$PWD/build
MOC_DIR = $$PWD/build
RCC_DIR = $$PWD/build
UI_DIR = $$PWD/build

#DEFINES =
