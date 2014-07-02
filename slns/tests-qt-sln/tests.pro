TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

# !!!
#QMAKE_CXXFLAGS += -std=c++11  # TODO: это влияет на весь код?

BOOST_PATH = /home/zaqwes/work/third_party/boost_1_55_0

INCLUDEPATH += \
    ../../../third_party/gmock-1.6.0/fused-src/ \
    ../../../third_party/loki-0.1.7/include/ \
    $$BOOST_PATH/stage_ia32/include

# -lrt !!
# http://stackoverflow.com/questions/2418157/ubuntu-linux-c-error-undefined-reference-to-clock-gettime-and-clock-settim
LIBS += -lpthread -lrt -L$$BOOST_PATH/stage_ia32/lib -lboost_thread -lboost_system

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
    ../../src/lang/equal_compare_test.cc \
    ../../src/lang/idioms_test.cc \
    ../../src/parallel/use_mutex_test.cc \
    ../../src/learn/sutter_tasks/exception_safety_test.cc \
    ../../src/learn/sutter_tasks/stl_test.cc \
    ../../src/learn/sutter_tasks_new/templ_stl_test.cc \
    ../../src/apps/stl_queries_apps.cc \
    ../../src/learn/sutter_tasks_new/classes_inh_pol_test.cc \
    ../../src/apps/pkgs_queue_apps.cc \
    ../../src/apps/persist_apps.cc \
    ../../src/apps/compact_apps.cc \
    ../../src/lang/ref_conters_cow_test.cc \
    ../../src/lang/ctor_rule_of_three_raii_and_swap_test.cc \
    ../../src/apps/no_new_loops_apps.cc \
    ../../src/apps/inh_evil_reduce_apps.cc \
    ../../src/apps/linux_apps.cc \
    #../../src/cpp11/base_test.cc

HEADERS += \
    ../../third_party/loki-0.1.7/include/loki/ScopeGuard.h

