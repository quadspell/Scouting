#-------------------------------------------------
#
# Project created by QtCreator 2014-01-26T12:54:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ScoutingProgram
TEMPLATE = app


SOURCES += main.cpp\
        startup.cpp \
    overloads.cpp \
    eventeditor.cpp \
    teameditor.cpp \
    teamstats.cpp \
    schedule.cpp \
    scoutingmode.cpp

HEADERS  += startup.h \
    overloads.h \
    team.h \
    eventeditor.h \
    teameditor.h \
    teamstats.h \
    schedule.h \
    scoutingmode.h
