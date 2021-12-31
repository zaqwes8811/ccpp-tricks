
add_executable(tsan_check
        ${CMAKE_SOURCE_DIR}/projects/all_tests.cc
#        bug_boost_ref_races_test.cc
#        nondetect_races_with_main_thread_test.cc
#        rw_semaphore_test.cc
        )


target_link_libraries(tsan_check
        ${GTEST_BOTH_LIBRARIES}
        pthread dl m rt
        )




