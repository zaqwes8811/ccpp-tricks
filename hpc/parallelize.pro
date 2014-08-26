TARGET = a.app
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

# Libs
BOOST=/home/zaqwes/work/third_party/boost_1_55_0
DETAILS=..
_3RD_PARTY=../3rdparty

# но лучше бы 11 убрать, т.к. не ясно нужно ли доопределять некоторые функции
# -std=c++11
# Opt. keys:
# http://publib.boulder.ibm.com/infocenter/comphelp/v7v91/index.jsp?topic=%2Fcom.ibm.xlf91a.doc%2Fxlfug%2Fhu00509.htm
QMAKE_CXXFLAGS += -O3  -Wall -Wno-deprecated -pg -std=c++11

SOURCES += \
  ../launcher.cc \
  $$_3RD_PARTY/gmock-1.6.0/fused-src/gmock-gtest-all.cc \
  ./tbb/base_test.cc #\
  #w3_dyn_pro.cc \
  #$$DETAILS/details/io_details.cc


INCLUDEPATH += \
  $$BOOST $$DETAILS $$DETAILS/.. \
  $$_3RD_PARTY/gmock-1.6.0/fused-src/

LIBS += -lpthread -lrt -ltbb

OBJECTS_DIR = obj