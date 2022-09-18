
add_executable(fastware_test
        ${CMAKE_SOURCE_DIR}/projects/all_tests.cc
        ben_deane/emplace_test.cpp
#        jason_turner/jt_perf.cpp
        )


target_link_libraries(fastware_test
        ${GTEST_BOTH_LIBRARIES}
        pthread dl m rt
        )

add_executable(fastware_bench
        ${CMAKE_SOURCE_DIR}/projects/all_benches.cpp
        )


target_link_libraries(fastware_bench
        ${GTEST_BOTH_LIBRARIES}
        pthread dl m rt
        )

