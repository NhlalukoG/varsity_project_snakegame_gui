QT       += core gui \
    multimedia
#QT       +=multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MainWindow
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Old config

#TARGET = MainWindow
#CONFIG += console
#CONFIG -= app_bundle
#QT += core
#QT += widgets
#QT += gui

CONFIG += c++11

TEMPLATE = app

SOURCES +=  main.cpp \
        mainwindow.cpp\
    startscreen.cpp \
    about.cpp \
    paused.cpp \
    timer.cpp \
    help.cpp \
    highscore.cpp \
    gameover.cpp

RESOURCES += \
    images.qrc

HEADERS += \
        mainwindow.h\
    startscreen.h \
    about.h \
    paused.h \
    timer.h \
    help.h \
    highscore.h \
    gameover.h

FORMS += \
         mainwindow.ui\
    startscreen.ui \
    about.ui \
    paused.ui \
    timer.ui \
    help.ui \
    highscore.ui \
    gameover.ui
