#-------------------------------------------------
#
# Project created by QtCreator 2020-05-29T12:10:29
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MySQLRecordCreater
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    connectionpool.cpp \
    insertthread.cpp \
    value.cpp \
    mybar.cpp

HEADERS  += mainwindow.h \
    connectionpool.h \
    insertthread.h \
    value.h \
    mybar.h

FORMS    += mainwindow.ui
