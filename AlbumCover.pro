#-------------------------------------------------
#
# Project created by QtCreator 2016-12-25T22:33:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AlbumCover
TEMPLATE = app

SOURCES += main.cpp\
        AlbumCover.cpp \
    MP3FileInfo.cpp \
    ScrollableArea.cpp

HEADERS  += AlbumCover.h \
    MP3FileInfo.h \
    ScrollableArea.h

unix|win32: LIBS += -L$$PWD/lib/lib/ -ltaglib

INCLUDEPATH += $$PWD/lib/include
DEPENDPATH += $$PWD/lib/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/lib/lib/taglib.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/lib/lib/libtaglib.a
