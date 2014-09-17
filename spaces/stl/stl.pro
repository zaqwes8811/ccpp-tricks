TARGET = a.app
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

# -pg -std=c++11
QMAKE_CXXFLAGS += -O2  -Wall -Wno-deprecated 

_3RD_PARTY=../../3rdparty

SOURCES += \
  insert_remove_erase_test.cc \
  containers_test.cc \
  algs/nomod_test.cc \
  algs/mod_test.cc \
  algs/sorted_test.cc \
  iter_func_test.cc \
  string_test.cc \
  io_test.cc \
  streams_test.cc \
  fun_pred_adapter_test.cc 

SOURCES += \
  $$_3RD_PARTY/gmock-1.6.0/fused-src/gmock-gtest-all.cc \
  ../../launcher.cc

INCLUDEPATH += \
  /home/zaqwes/work/third_party/source_release \
  /home/zaqwes/work/third_party/boost_1_55_0 \
  $$_3RD_PARTY/gmock-1.6.0/fused-src/ \
  $$_3RD_PARTY/loki-0.1.7/include/ \
  ../../
  
OBJECTS_DIR = obj

# -ltbb не достаточно
LIBS += -lpthread -lrt -ltbbmalloc -ltbb