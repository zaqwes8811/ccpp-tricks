TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += static

# C
QMAKE_CFLAGS_RELEASE -= -MD
QMAKE_CFLAGS_RELEASE = -MT
QMAKE_CFLAGS_DEBUG -= -MDd
QMAKE_CFLAGS_DEBUG = -MTd

# C++
QMAKE_CXXFLAGS_RELEASE -= -MD
QMAKE_CXXFLAGS_RELEASE += -MT
QMAKE_CXXFLAGS_DEBUG -= -MDd
QMAKE_CXXFLAGS_DEBUG += -MTd

SOURCES += main.cpp

INCLUDEPATH += "D:/home/third_party/cc/boost_1_47_0"
INCLUDEPATH += "C:/Python27/include"

LIBS += C:/Python27/libs/python27.lib

