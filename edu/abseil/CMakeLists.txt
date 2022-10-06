
add_executable(abseil_test
        ${CMAKE_SOURCE_DIR}/projects/all_tests.cc
        summary.cpp
        )


target_link_libraries(abseil_test
        ${GTEST_BOTH_LIBRARIES}
        pthread dl m rt
        )

####################################################################

find_package(benchmark REQUIRED)
include_directories(${benchmark_INCLUDE_DIRS})
link_libraries(${benchmark_LIBRARIES} pthread)

add_executable(abseil_bench
        ${CMAKE_SOURCE_DIR}/projects/all_benches.cpp
        )


target_link_libraries(abseil_bench
        ${GTEST_BOTH_LIBRARIES}
        pthread dl m rt
        )

