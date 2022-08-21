
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/loki-0.1.7/include)

add_executable(cc_core
        ${CMAKE_SOURCE_DIR}/projects/all_tests.cc
        containers_test.cc
        crt_pattern_test.cc
        fun_pred_adapter_test.cc
        insert_remove_erase_test.cc
        iters_test.cc
        marked_guidelines_test.cc
        move_idiom_test.cc
        pimpl_and_nvi_idiom_test.cc
        std_own_ext_test.cc
        stl_x64_test.cc
        streams_test.cc
        string_test.cc
        subtle_moments_test.cc
        types_test.cc
        )


target_link_libraries(cc_core
        ${GTEST_BOTH_LIBRARIES}
        pthread dl m rt
        )