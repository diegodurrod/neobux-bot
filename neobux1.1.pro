#-------------------------------------------------
#
# Project created by QtCreator 2013-09-16T15:20:04
#
#-------------------------------------------------

QT       += core gui webkitwidgets webkit
#QT      += webenginewidgets

TARGET = bot
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    url.cpp \
    tiempo.cpp \
    vector.cpp

HEADERS  += mainwindow.h \
    url.h \
    tiempo.h \
    vector.h \
    MyWebPage.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc

OTHER_FILES += \
    ToDo.txt
