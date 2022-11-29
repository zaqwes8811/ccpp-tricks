include_directories(${CMAKE_SOURCE_DIR}/3rdparty/loki-0.1.7/include)

add_executable(cpptemplates_book
        ${CMAKE_SOURCE_DIR}/projects/all_tests.cc
        ch28_debugging_templates.cpp
        )


target_link_libraries(cpptemplates_book
        ${GTEST_BOTH_LIBRARIES}
        pthread dl m rt
        )
