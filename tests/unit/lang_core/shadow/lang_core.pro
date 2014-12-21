TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt



SOURCES += ./inheritance_test.cc \
  ../../third_party/gmock-1.6.0/fused-src/gmock-gtest-all.cc \
  ../launcher.cc

INCLUDEPATH += ../../third_party/gmock-1.6.0/fused-src/

LIBS += -lpthread -lrt