# -DCMAKE_BUILD_TYPE=Debug
# -DCMAKE_VERBOSE_MAKEFILE=ON -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++
#
# x64:
#  https://developer.apple.com/library/mac/documentation/Darwin/Conceptual/64bitPorting/building/building.html
#  http://stackoverflow.com/questions/16273561/gcc-generic-march-for-all-the-x64-platforms

project(x64-learn)
cmake_minimum_required(VERSION 2.8)

add_executable(x64-learn
    ${CMAKE_SOURCE_DIR}/projects/all_tests.cc
    viva64_test.cc
)

target_link_libraries(x64-learn
        ${GTEST_BOTH_LIBRARIES}
        pthread dl m rt
        )
