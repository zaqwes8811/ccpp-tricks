TARGET = a.app
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt


SOURCES += ./no_raw_loops_app.cc #\
  #../../third_party/gmock-1.6.0/fused-src/gmock-gtest-all.cc \
  #../launcher.cc

INCLUDEPATH += /home/zaqwes/work/third_party/source_release
  #../../third_party/gmock-1.6.0/fused-src/

LIBS += -lpthread -lrt