#-------------------------------------------------
#
# Project created by QtCreator 2016-05-29T21:39:38
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TareaF1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    robot.cpp \
    glwidget.cpp \
    map.cpp \
    threadrobot.cpp \
    threadmap.cpp

HEADERS  += mainwindow.h \
    robot.h \
    glwidget.h \
    map.h \
    threadrobot.h \
    threadmap.h

FORMS    += mainwindow.ui


INCLUDEPATH += /usr/local/Aria/include

LIBS += -L/usr/local/Aria/lib/ \
    -lAria -ldl -lrt -lm
