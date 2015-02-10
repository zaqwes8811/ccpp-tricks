TARGET = a.app
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

# Libs
BOOST=/home/zaqwes/work/third_party/boost_1_55_0
DETAILS=..
_3RD_PARTY=../../3rdparty
ADOBE_SL=/home/zaqwes/work/third_party/source_release

# но лучше бы 11 убрать, т.к. не ясно нужно ли доопределять некоторые функции
# Opt. keys:
# http://publib.boulder.ibm.com/infocenter/comphelp/v7v91/index.jsp?topic=%2Fcom.ibm.xlf91a.doc%2Fxlfug%2Fhu00509.htm
# -pg -std=c++11
QMAKE_CXXFLAGS += -O3  -Wall -Wno-deprecated 

SOURCES += \
  boost_cc98/thread_safe_boost_sync_test.cc \
  boost_cc98/use_mutex_test.cc \
  boost_cc98/prod_consumer_pattern_test.cc \
  tbb/base_test.cc
  
SOURCES += \
  ../../toolbox/launcher.cc \
  $$_3RD_PARTY/gmock-1.6.0/fused-src/gmock-gtest-all.cc \

INCLUDEPATH += \
  $$BOOST \
  $$DETAILS \
  $$DETAILS/.. \
  $$ADOBE_SL \
  $$_3RD_PARTY/gmock-1.6.0/fused-src/


LIBS += -lpthread -lrt -ltbb
LIBS += -L$$BOOST/stage/lib -lboost_thread -lboost_system

OBJECTS_DIR = obj