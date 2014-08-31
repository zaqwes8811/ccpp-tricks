TARGET = a.app
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
OBJECTS_DIR = obj

# -std=c++11
QMAKE_CXXFLAGS += -O2  -Wall -Wno-deprecated 

_3RD_PARTY=../../3rdparty
BOOST=/home/zaqwes/work/third_party/boost_1_55_0

SOURCES += \
  ./ch9_conc_parall_test.cc \
  eff_conc_test.cc \
  $$_3RD_PARTY/gmock-1.6.0/fused-src/gmock-gtest-all.cc \
  ../../launcher.cc

INCLUDEPATH += \
  /home/zaqwes/work/third_party/source_release \
  /home/zaqwes/work/third_party/threadpool-0_2_5-src/threadpool \
  $$BOOST \
  $$_3RD_PARTY/gmock-1.6.0/fused-src/ \
  ../../

LIBS += -lpthread -lrt -ltbb
LIBS += -L$$BOOST/stage/lib -lboost_thread -lboost_system