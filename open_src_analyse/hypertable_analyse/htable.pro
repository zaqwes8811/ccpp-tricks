TARGET = a.app
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
OBJECTS_DIR = obj

OWN_3RD_PARTY = ../../3rdparty

SOURCES += \
  ref_counting_test.cc \
  $$OWN_3RD_PARTY/gmock-1.6.0/fused-src/gmock-gtest-all.cc \
  ../../launcher.cc

INCLUDEPATH += \
  /home/zaqwes/work/third_party/source_release \
  /home/zaqwes/work/third_party/boost_1_55_0 \
  $$OWN_3RD_PARTY/gmock-1.6.0/fused-src/ \

LIBS += -lpthread -lrt