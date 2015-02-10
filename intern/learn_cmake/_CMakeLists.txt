# Tut.:
# http://mirkokiefer.com/blog/2013/03/cmake-by-example/


cmake_minimum_required (VERSION 2.6)
project (Tutorial)

# The version number.
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)
set (_3RD_PARYT "${CMAKE_CURRENT_SOURCE_DIR}/../../3rdparty/gmock-1.6.0/fused-src")
set (launcher ../../../launcher.cc)
set (TARGET_APP ../a.app)

add_definitions(-std=c++11)

include_directories(${_3RD_PARYT})

#file(GLOB helloworld_SRC
#    "*.h"
#    "*.cpp"
#)
#
#add_executable(helloworld ${helloworld_SRC})

# Linking external
# http://answers.ros.org/question/126951/cmake-linking-external-c-library/

# SHARED STATIC
# странно как-то находит библиотеку.
add_library(gtest SHARED ${_3RD_PARYT}/gmock-gtest-all.cc)

add_executable("${TARGET_APP}" "${launcher}")
target_link_libraries("${TARGET_APP}" gtest)
target_link_libraries("${TARGET_APP}" pthread)
  
#target_link_libraries( pthread rt) 