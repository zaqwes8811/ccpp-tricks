TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ../../../third_party/gmock-1.6.0/fused-src/

LIBS += -lpthread

SOURCES += \
    ../../../third_party/gmock-1.6.0/fused-src/gmock-gtest-all.cc \
    ../../src/lang/tests-launcher.cc \
    ../../src/lang/inheritance_test.cc

