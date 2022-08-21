include_directories(${CMAKE_SOURCE_DIR}/3rdparty/loki-0.1.7/include)

add_executable(gc
        ${CMAKE_SOURCE_DIR}/projects/all_tests.cc
        mem_and_resources_test.cc
        mem_pools_test.cc
        mm_files_test.cc
        own_alloc_test.cc
        ref_count_chromium_test.cc
        shild_gc_single_thread_test.cc
        smart_ptrs_in_depth_test.cc
        )


target_link_libraries(gc
        ${GTEST_BOTH_LIBRARIES}
        pthread dl m rt
        )
