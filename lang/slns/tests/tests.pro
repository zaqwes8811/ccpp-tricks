TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ../../../third_party/gmock-1.6.0/fused-src/

SOURCES += \
    ../../../third_party/gmock-1.6.0/fused-src/gmock-gtest-all.cc \
    ../../src/tests-launcher.cc \
    ../../src/inheritance_test.cc

