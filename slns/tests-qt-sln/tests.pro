TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ../../../third_party/gmock-1.6.0/fused-src/

LIBS += -lpthread

SOURCES += \
    ../../../third_party/gmock-1.6.0/fused-src/gmock-gtest-all.cc \
    ../../src/tests-launcher.cc \
    ../../src/lang/inheritance_test.cc \
    ../../src/learn/sutter_tasks/mem_and_resources_6_test.cc \
    ../../src/memory/smart_ptrs_in_depth_test.cc \
    ../../src/learn/shild/gc_single_thread_test.cc \
    ../../src/stl/stl_and_base_ops_test.cc \
    ../../src/stl/stl_algs_test.cc \
    ../../src/stl/stl_iter_func_test.cc \
    ../../src/lang/rule_of_three_and_equal_compare_test.cc

