# debig troubles
# http://stackoverflow.com/questions/19912648/cmake-qtcreator-mingw-debug-mode-windows-7
# http://www.cmake.org/Wiki/CMake_Useful_Variables
# -DCMAKE_BUILD_TYPE=Debug
# -DCMAKE_VERBOSE_MAKEFILE=ON -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++

project(new_cpp)
cmake_minimum_required(VERSION 2.8)

find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 17)

# link the libraries to the executable
if (UNIX)
    link_libraries(tbb tbbmalloc boost_system boost_thread pthread rt)  # !! pthread and rt last!!
endif ()

IF (LCB_USE_ASAN)
    # main: address - thread, memory and ub not work in i686, only x86_64
    #-fno-omit-frame-pointer -O1
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g  -fsanitize=address")
    #-fno-omit-frame-pointer -O1
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -g  -fsanitize=address")
    # -undefined dynamic_lookup
    SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS}  -fsanitize=address")
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
    add_definitions(-Wall -g -fsanitize=address)
endif ()

# Sources
file(GLOB proTests
        ${testsRoot}/sutter_tasks_new/*.cc
        )


add_executable(unittest.bin
        core_tests.cc
        summary.cc
        )

target_link_libraries(unittest.bin PUBLIC
        ${GTEST_BOTH_LIBRARIES}
        Threads::Threads)


