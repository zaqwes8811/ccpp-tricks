# https://stackoverflow.com/questions/58807225/google-benchmark-as-a-cmake-dependency
# https://cmake.org/cmake/help/latest/command/find_package.html
project(hp)
cmake_minimum_required(VERSION 3.10)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/../cmake" CACHE STRING "Modules for CMake" FORCE)

find_package(benchmark REQUIRED)

include_directories(${benchmark_INCLUDE_DIRS})
link_libraries(${benchmark_LIBRARIES} pthread)

add_executable(hp lru.cc)
