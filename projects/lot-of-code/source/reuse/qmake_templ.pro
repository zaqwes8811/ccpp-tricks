# http://stackoverflow.com/questions/2580934/how-to-specify-different-debug-release-output-directories-in-qmake-pro-file

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

TARGET = sample.app

BOOST=/home/zaqwes/work/third_party/boost_1_55_0

QMAKE_CXXFLAGS += -O2 -std=c++11 -Wall -Wno-deprecated -pg

SOURCES += w1_greedy.cc 
#\
#  ../../third_party/gmock-1.6.0/fused-src/gmock-gtest-all.cc \
#  ../launcher.cc

INCLUDEPATH += $$BOOST
#../../third_party/gmock-1.6.0/fused-src/

LIBS += -lpthread -lrt -ltbb

OBJECTS_DIR = obj


HEADERS += src/dialogs.h
SOURCES += src/main.cpp \
           src/dialogs.cpp

Release:DESTDIR = release
Release:OBJECTS_DIR = release/.obj
Release:MOC_DIR = release/.moc
Release:RCC_DIR = release/.rcc
Release:UI_DIR = release/.ui

Debug:DESTDIR = debug
Debug:OBJECTS_DIR = debug/.obj
Debug:MOC_DIR = debug/.moc
Debug:RCC_DIR = debug/.rcc
Debug:UI_DIR = debug/.ui