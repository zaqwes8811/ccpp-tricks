TEMPLATE = app
CONFIG += console
CONFIG -= qt

# !!!
QMAKE_CXXFLAGS += -std=c++11  # TODO: это влияет на весь код?

BOOST_PATH = /home/zaqwes/work/third_party/boost_1_55_0

INCLUDEPATH += \
    ../../../third_party/gmock-1.6.0/fused-src/ \
    #../../../third_party/loki-0.1.7/include/ \
    $$BOOST_PATH/stage_ia32/include

# -lrt !!
# http://stackoverflow.com/questions/2418157/ubuntu-linux-c-error-undefined-reference-to-clock-gettime-and-clock-settim
LIBS += -lpthread -lrt #-L$$BOOST_PATH/stage_ia32/lib -lboost_thread -lboost_system


SOURCES += \
    ../../src/tests-launcher.cc \
    ../../third_party/fused-src/gmock-gtest-all.cc \
    ../../src/cpp11/base_test.cc \
    ../../src/apps/inh_evil_reduce_c11_apps.cc \
    ../../src/apps/extend_evil_app.cc

