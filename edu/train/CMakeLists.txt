add_executable(train
        ${CMAKE_SOURCE_DIR}/projects/all_tests.cc
        my_recyclable_list_test.cc
        )


target_link_libraries(train
        ${GTEST_BOTH_LIBRARIES}
        pthread dl m rt
        )