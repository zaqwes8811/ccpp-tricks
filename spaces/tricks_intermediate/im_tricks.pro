TARGET = a.app
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
OBJECTS_DIR = obj

LOCAL_3RD_PARTY=../../3rdparty
TOOLBOX = ../../toolbox
GLOBAL_3RD_PARTY = /home/zaqwes/work/third_party

SOURCES += \
  pimpl_and_nvi_idiom_test.cc \
  smart_ptrs_in_depth_test.cc \
  move_idiom_test.cc \
  mem_pools_test.cc \
  smart_ptrs_in_depth_test.cc \
  mem_and_resources_test.cc \
  crt_pattern_test.cc \
  $$LOCAL_3RD_PARTY/gmock-1.6.0/fused-src/gmock-gtest-all.cc \
  $$TOOLBOX/launcher.cc

INCLUDEPATH += \
  $$GLOBAL_3RD_PARTY/source_release \
  $$GLOBAL_3RD_PARTY/boost_1_55_0 \
  $$LOCAL_3RD_PARTY/gmock-1.6.0/fused-src/ \
  $$LOCAL_3RD_PARTY/loki-0.1.7/include \
  $$TOOLBOX

LIBS += -lpthread -lrt