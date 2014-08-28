TARGET = a.app
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
OBJECTS_DIR = obj

QMAKE_CXXFLAGS += -O2 -std=c++11 -Wall -Wno-deprecated -pg


SOURCES += \
  ./ch9_conc_parall_test.cc \
  eff_conc_test.cc \
  ../../../third_party/gmock-1.6.0/fused-src/gmock-gtest-all.cc \
  ../../launcher.cc

INCLUDEPATH += /home/zaqwes/work/third_party/source_release \
  /home/zaqwes/work/third_party/boost_1_55_0 \
  ../../../third_party/gmock-1.6.0/fused-src/ \
  ../../

LIBS += -lpthread -lrt -ltbb