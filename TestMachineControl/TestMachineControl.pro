QT += testlib
QT -= gui

QT += serialport

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_machinecontrol.cpp

INCLUDEPATH += $$PWD/../sources
#
SOURCES += $$PWD/../sources/MachineControlAI.cpp
#
HEADERS += $$PWD/../sources/MachineControlAI.h
