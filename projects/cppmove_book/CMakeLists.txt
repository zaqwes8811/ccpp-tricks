include_directories(${CMAKE_SOURCE_DIR}/3rdparty/loki-0.1.7/include)

add_executable(cppmove_book
        ${CMAKE_SOURCE_DIR}/projects/all_tests.cc
        perfect_forwarding.cpp
        )


target_link_libraries(cppmove_book
        ${GTEST_BOTH_LIBRARIES}
        pthread dl m rt
        )
