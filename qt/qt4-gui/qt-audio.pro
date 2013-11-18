
QMAKE_CXXFLAGS += -std=c++11

QT += multimedia widgets

CONFIG += debug

SOURCES += main.cpp

HEADERS += Application.h
SOURCES += Application.cpp

HEADERS += MainWindow.h
SOURCES += MainWindow.cpp

HEADERS += CentralWidget.h
SOURCES += CentralWidget.cpp

HEADERS += AudioSource.h
SOURCES += AudioSource.cpp
