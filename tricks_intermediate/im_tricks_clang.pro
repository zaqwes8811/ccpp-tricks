TARGET = a.app
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
OBJECTS_DIR = obj

# compilers
# /home/zaqwes/tools/third_party/llvm-build/Release+Asserts/bin/
QMAKE_CXX=clang++
QMAKE_CXXFLAGS += -emit-llvm
#QMAKE_CXX = clang++
QMAKE_CC = clang
QMAKE_LINK = clang++  #llvm-ld

SOURCES += \
  pimpl_and_nvi_idiom_test.cc \
  smart_ptrs_in_depth_test.cc \
  move_idiom_test.cc \
  mem_pools_test.cc \
  smart_ptrs_in_depth_test.cc \
  mem_and_resources_test.cc \
  crt_pattern_test.cc \
  ../3rdparty/gmock-1.6.0/fused-src/gmock-gtest-all.cc \
  ../launcher.cc

INCLUDEPATH += \
  /home/zaqwes/work/third_party/source_release \
  /home/zaqwes/work/third_party/boost_1_55_0 \
  ../3rdparty/gmock-1.6.0/fused-src/ \
  ../3rdparty/loki-0.1.7/include \
  ../

LIBS += -lpthread -lrt