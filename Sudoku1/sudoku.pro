#-------------------------------------------------
#
# Project created by QtCreator 2019-04-20T20:18:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sudoku
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    solver.cpp \
    dancinglink.cpp \
    sudoku.cpp

HEADERS  += mainwindow.h \
    debug.h \
    const.h \
	solver.h \
    dancinglink.h \
    sudoku.h

FORMS    += mainwindow.ui
