TEMPLATE = app
CONFIG += console
CONFIG -= qt

CONFIG+=r16258

INCLUDEPATH += \
    ../../../../third_party/gmock-1.6.0/fused-src \
    /home/zaqwes/work/third_party \
    ../../src

LIBS += -lpthread

r16258 {
LIBS += -L/home/zaqwes/work/third_party/v8-r16258/out/ia32.release/obj.target/tools/gyp -lv8_base.ia32 -lv8_nosnapshot.ia32

}

SOURCES += \
    ../../src/launcher_process.cc \
    ../../../../third_party/gmock-1.6.0/fused-src/gmock-gtest-all.cc \
    ../../src/raw/point.cc

r16258 {
SOURCES += \
    ../../src/v8-r16258/v8_api_test.cc \
    ../../src/v8-r16258/process.cc \
    ../../src/v8-r16258/process_test.cc
}

