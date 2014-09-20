TARGET = a.app
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

# -pg -std=c++11
QMAKE_CXXFLAGS += -O2  -Wall -Wno-deprecated 

LOCAL_3RD_PARTY=../../../3rdparty
TOOLBOX = ../../../toolbox
GLOBAL_3RD_PARTY = /home/zaqwes/work/third_party

SOURCES += \
  alg_composite/insert_remove_erase_test.cc \
  containers/containers_test.cc \
  containers/containers_benchmark.cc \
  algs/nomod_test.cc \
  algs/mod_test.cc \
  algs/sorted_test.cc \
  algs/own_test.cc \
  algs/del_test.cc \
  string_test.cc \
  streams_test.cc \
  iters_test.cc \
  fun_pred_adapter_test.cc 

SOURCES += \
  $$LOCAL_3RD_PARTY/gmock-1.6.0/fused-src/gmock-gtest-all.cc \
  $$TOOLBOX/launcher.cc

INCLUDEPATH += \
  $$GLOBAL_3RD_PARTY/source_release \
  $$GLOBAL_3RD_PARTY/boost_1_55_0 \
  $$LOCAL_3RD_PARTY/gmock-1.6.0/fused-src/ \
  $$LOCAL_3RD_PARTY/loki-0.1.7/include/ \
  $$TOOLBOX
  
OBJECTS_DIR = obj

# -ltbb не достаточно
LIBS += -lpthread -lrt -ltbbmalloc -ltbb