add_executable(asan_check
        ${CMAKE_SOURCE_DIR}/projects/all_tests.cc
        banch_of_test.cc
        bug_container_resize_test.cc
        summary_test.cc
        working_asan_test.cc
        )


target_link_libraries(asan_check
        ${GTEST_BOTH_LIBRARIES}
        pthread dl m rt
        )

