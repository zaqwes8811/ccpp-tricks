
add_executable(tricks
        ${CMAKE_SOURCE_DIR}/projects/all_tests.cc
        sutter_tasks_new/classes_inh_pol_test.cc
        sutter_tasks_new/templ_stl_test.cc
        sutter_tasks/exception_safety_test.cc
        sutter_tasks/mem_and_resources_6_test.cc
        sutter_tasks/stl_test.cc
        sean_parent/goal_no_raw_loops_app.cc
        sean_parent/goal_no_raw_ptrs_app.cc
        sean_parent/goal_no_raw_sync_primitives_app.cc
        sean_parent/inh_evil_reduce_c98_apps.cc
        from_gotchas/ch1_test.cc
        from_gotchas/ch5_init.cc
        from_gotchas/ch7_poly_test.cc
        from_gotchas/ch8.cc
        coding_standarts/ctors_dtors_assign.cc
        )


target_link_libraries(tricks
        ${GTEST_BOTH_LIBRARIES}
        pthread dl m rt
        )


add_subdirectory(cppmove_book)
add_subdirectory(opt_cpp)