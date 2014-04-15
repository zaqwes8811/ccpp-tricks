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
    ../../src/raw/point.cc \
    ../../src/raw/palette.cc


r16258 {
SOURCES += \
    ../../src/v8-r16258/v8_api_test.cc \
    ../../src/v8-r16258/process.cc \
    ../../src/v8-r16258/process_test.cc \
    ../../src/v8-r16258/process_test_ext_test.cc \
    ../../src/v8-r16258/point_expose_test.cc \
    ../../src/v8-r16258/point_engine_test.cc \
    ../../src/v8-r16258/palette_engine_test.cc \
    ../../src/v8-r16258/process_test_ext.cc \
    ../../src/v8-r16258/v8_wrapper.cc \
    ../../src/v8-r16258/js_request.cc \
    ../../src/v8-r16258/virtual_machine.cc \
    ../../src/v8-r16258/v8_wrapper_db.cc \
    ../../src/v8-r16258/arrays_test.cc \
    ../../src/v8-r16258/engine_cut_persistents.cc \
    ../../src/v8-r16258/database_manipulations.cc
}

