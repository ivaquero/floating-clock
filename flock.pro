# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

TARGET = flock

QT = core gui widgets

SOURCES = \
   $$PWD/main.cpp \
   $$PWD/clockwidget.cpp \
   $$PWD/configmanager.cpp

HEADERS = \
   $$PWD/clockwidget.h \
   $$PWD/configmanager.h

INCLUDEPATH = \
    $$PWD/.

# Set build output directories
DESTDIR = $$PWD/build
OBJECTS_DIR = $$PWD/build
MOC_DIR = $$PWD/build
RCC_DIR = $$PWD/build
UI_DIR = $$PWD/build

#DEFINES =
