TARGET = a.app
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
OBJECTS_DIR = obj


SOURCES += \
  pimpl_and_nvi_idiom_test.cc \
  smart_ptrs_in_depth_test.cc \
  move_idiom_test.cc \
  smart_ptrs_in_depth_test.cc \
  mem_and_resources_test.cc \
  ../../third_party/gmock-1.6.0/fused-src/gmock-gtest-all.cc \
  ../launcher.cc

INCLUDEPATH += /home/zaqwes/work/third_party/source_release \
  /home/zaqwes/work/third_party/boost_1_55_0 \
  ../../third_party/gmock-1.6.0/fused-src/ \
  ../

LIBS += -lpthread -lrt