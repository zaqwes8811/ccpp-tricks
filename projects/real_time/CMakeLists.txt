project(rt_audio)
cmake_minimum_required(VERSION 2.8)

find_package(benchmark REQUIRED)
include_directories(${benchmark_INCLUDE_DIRS})
link_libraries(${benchmark_LIBRARIES} pthread)

find_package(GTest REQUIRED)

find_package(iceoryx_hoofs REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(rt_audio
        ${CMAKE_SOURCE_DIR}/projects/all_benches.cpp
        iceoyx_hoofs_test.cpp
        )


target_link_libraries(rt_audio
        ${GTEST_BOTH_LIBRARIES}
        pthread dl m rt
        )