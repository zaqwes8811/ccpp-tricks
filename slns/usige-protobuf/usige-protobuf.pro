TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

# C
Release:QMAKE_CFLAGS_RELEASE -= -MD
Debug:QMAKE_CFLAGS_DEBUG -= -MDd
Release:QMAKE_CFLAGS_RELEASE += -MT
Debug:QMAKE_CFLAGS_DEBUG += -MTd
# C++
Release:QMAKE_CXXFLAGS_RELEASE -= -MD
Debug:QMAKE_CXXFLAGS_DEBUG -= -MDd
Release:QMAKE_CXXFLAGS_RELEASE += -MT
Debug:QMAKE_CXXFLAGS_DEBUG += -MTd

INCLUDEPATH += ../../third_party/gmock-1.6.0/fused-src/

SOURCES += \
    ../../src/lang/tests-launcher.cc \
    ../../src/serialize/protobuf_filter_test.cc \
    ../../third_party/gmock-1.6.0/fused-src/gmock-gtest-all.cc

