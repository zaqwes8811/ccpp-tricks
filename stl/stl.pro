TARGET = a.app
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

_3RD_PARTY=../3rdparty

SOURCES += \
  insert_remove_erase_test.cc \
  containers_test.cc \
  algs_test.cc \
  iter_func_test.cc \
  string_app.cc \
  base_ops_test.cc \
  fun_pred_adapter_test.cc \
  $$_3RD_PARTY/gmock-1.6.0/fused-src/gmock-gtest-all.cc \
  ../launcher.cc

INCLUDEPATH += /home/zaqwes/work/third_party/source_release \
  /home/zaqwes/work/third_party/boost_1_55_0 \
  $$_3RD_PARTY/gmock-1.6.0/fused-src/ \
  ../
  
OBJECTS_DIR = obj

# -ltbb не достаточно
LIBS += -lpthread -lrt -ltbbmalloc -ltbb