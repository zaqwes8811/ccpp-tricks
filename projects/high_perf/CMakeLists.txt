# https://stackoverflow.com/questions/58807225/google-benchmark-as-a-cmake-dependency
# https://cmake.org/cmake/help/latest/command/find_package.html
project(performance_and_rt)
cmake_minimum_required(VERSION 3.10)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/../cmake" CACHE STRING "Modules for CMake" FORCE)

include_directories(${CMAKE_SOURCE_DIR}/3rdparty/llvm-project/llvm/include)
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/llvm-project/llvm_autogen/include)

find_package(benchmark REQUIRED)
include_directories(${benchmark_INCLUDE_DIRS})
link_libraries(${benchmark_LIBRARIES} pthread)

include_directories(${CMAKE_SOURCE_DIR}/3rdparty)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

# https://stackoverflow.com/questions/26749461/how-to-determine-the-boost-library-names-for-cmake
find_package(Boost 1.51.0 REQUIRED)

add_executable(performance_and_rt
        ${CMAKE_SOURCE_DIR}/projects/all_benches.cpp
        ${CMAKE_SOURCE_DIR}/3rdparty/llvm-project/llvm/lib/Support/ABIBreak.cpp
        ${CMAKE_SOURCE_DIR}/3rdparty/llvm-project/llvm/lib/Support/MemAlloc.cpp
        #        ${CMAKE_SOURCE_DIR}/3rdparty/llvm-project/llvm/unittests/ADT/ImmutableMapTest.cpp  # need lot of code to link with
#        small_data_structs_test.cc
#        copy_removal_tricks_test.cpp
#        buffer.cpp
#        llvm_small_objects_test.cpp
#        rt_test.cpp
#        folly_test.cpp
        zigzag_test.cpp
        )

target_link_libraries(performance_and_rt
        ${GTEST_BOTH_LIBRARIES}
        pthread dl m rt
        )

################################################################################

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer -g -ggdb3")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fno-omit-frame-pointer -g -ggdb3")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fno-omit-frame-pointer -g -ggdb3")

add_executable(hp_benchmark
        ${CMAKE_SOURCE_DIR}/projects/all_benches.cpp
        zigzag_benchmark.cpp
        )

target_link_libraries(hp_benchmark
        ${GTEST_BOTH_LIBRARIES}
        pthread dl m rt
        )
