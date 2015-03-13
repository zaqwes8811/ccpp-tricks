# debig troubles
# http://stackoverflow.com/questions/19912648/cmake-qtcreator-mingw-debug-mode-windows-7
# http://www.cmake.org/Wiki/CMake_Useful_Variables
# -DCMAKE_BUILD_TYPE=Debug
# -DCMAKE_VERBOSE_MAKEFILE=ON -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++

project(cc-tricks)
cmake_minimum_required(VERSION 2.8)

set(Extern "../../extern/")
set(GMock "../../extern/gmock-1.6.0/fused-src")
set(Canary "./source/canary/")
set(Pro "./source/production/")
set(unitTests "./tests/")
set(Source "source/")
set(testsRoot "./tests")
set(root ".")
set(BigExtern "/home/zaqwes/work/big-3rdparty/")
set(Intern "../../intern/")

# Test framework
include_directories(${GMock})
include_directories(${Source})
include_directories(${Extern}/loki-0.1.7/include)
include_directories(${Extern})
include_directories(${BigExtern}/boost_1_57_0)
include_directories(${unitTests})
include_directories(${Intern})

# link the libraries to the executable
if (MINGW)
  file( GLOB toRemoveSnmpAgent ${Pro}/win_snmp_update/*.cc ${Pro}/win_snmp_update/*.h)
  # Mingw c++11 troubles
  # https://www.ics.uci.edu/~pattis/common/modules46/googletest.html
  # http://stackoverflow.com/questions/13198712/trouble-building-tests-with-google-test-clang-and-libc
  # https://code.google.com/p/googletest/issues/detail?id=422
  # -stdlib=libc++  - not work
  # -std=gnu++11
  # http://stackoverflow.com/questions/15053776/how-do-you-disable-the-unused-variable-warnings-coming-out-of-gcc
  # -Wno-unused-variable
  link_directories(${BigExtern}/boost_1_57_0/stage/lib)
  add_definitions(  -Wall -Wno-unused-local-typedefs)# -Wincompatible-pointer-types)
  #add_definitions(-DGTEST_USE_OWN_TR1_TUPLE=1 -DGTEST_HAS_TR1_TUPLE=1)
  LINK_LIBRARIES(ws2_32 WSnmp32 boost_system-mgw48-mt-s-1_57)
elseif (MSVC90)
  file( GLOB toRemoveSnmpAgent ${Pro}/win_snmp_update/*.cc ${Pro}/win_snmp_update/*.h)
  # FIXME: C runtime troubles
  # http://stackoverflow.com/questions/14172856/cmake-compile-with-mt-instead-of-md
  # http://msdn.microsoft.com/en-us/library/2kzt1wy3.aspx
  # http://stackoverflow.com/questions/757418/should-i-compile-with-md-or-mt
  #
  # http://rsdn.ru/forum/cpp.applied/2843738.hot
  # /MT
  link_directories(${BigExtern}/boost_1_57_0/stage/lib)
  add_definitions( -D_CRT_SECURE_NO_WARNINGS)# /showIncludes)#D)#T)
  #set(CMAKE_CXX_FLAGS_RELEASE "/MT")

  # Failure
  #set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
  #set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
  LINK_LIBRARIES(ws2_32 WSnmp32 libboost_system-vc90-mt-1_57)# libboost_thread-vc90-mt-s-1_57.lib)
elseif (UNIX)
  # gcc 4.8 ubuntu 12 http://llvm.org/docs/GettingStarted.html#getting-a-modern-host-c-toolchain
  # cmake .. -DCMAKE_CXX_LINK_FLAGS="-Wl,-rpath,$HOME/toolchains/lib64 -L$HOME/toolchains/lib64"
  # http://llvm.org/docs/GettingStarted.html#getting-a-modern-host-c-toolchain

  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message("I'm clang")
    link_directories(${BigExtern}/boost_1_57_0/stage_gcc/lib)
    link_libraries(tbb tbbmalloc boost_system boost_thread pthread rt)  # !! pthread and rt last!!
  else()
    message("I'm NOT clang")
    add_definitions(  -Wall)
    # FIXME: -D_REENTRANT
    if (CMAKE_SYSTEM_PROCESSOR MATCHES arm)
      link_directories(${BigExtern}/boost_1_57_0/stage_arm/lib)
      link_libraries(pthread boost_system)
      message("I'm ARM processor")
      # http://stackoverflow.com/questions/11944060/how-to-detect-target-architecture-using-cmake
      #  message( STATUS "Architecture: ${ARCHITECTURE}" ) # not work
    else()
      message("I'm NOT ARM processor")
      link_directories(${BigExtern}/boost_1_57_0/stage_x64/lib)
      # how split embedded form just linux
      # http://stackoverflow.com/questions/9534126/automatically-linking-socket-shared-library-in-nix
      # http://stackoverflow.com/questions/14835605/linking-with-gcc-fails-after-switching-boost-version-from-1-52-to-1-53
      #
      # http://stackoverflow.com/questions/9511422/undefined-reference-to-clock-gettime-gcc-4-6-cmake
      # http://www.unix.com/man-page/opensolaris/3lib/librt/
      #
      # https://software.intel.com/en-us/forums/topic/285308
      link_libraries(tbb tbbmalloc boost_system boost_thread pthread rt)  # !! pthread and rt last!!
    endif()
  endif()
endif()

IF(LCB_USE_ASAN)
    # main: address - thread, memory and ub not work in i686, only x86_64
    #-fno-omit-frame-pointer -O1
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g  -fsanitize=address")
    #-fno-omit-frame-pointer -O1
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -g  -fsanitize=address")
    # -undefined dynamic_lookup
    SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS}  -fsanitize=address")
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
    add_definitions(  -Wall -g -fsanitize=address)
endif()

# Sources
file( GLOB proTests
  ${testsRoot}/sutter_tasks_new/*.cc
  ${testsRoot}/intermediate/*.cc
  ${testsRoot}/stephan_t_lavavej/*.cc
  ${unitTests}/tricks_peoples/sutter_tasks/*.cc
  ${unitTests}/tricks_peoples/sutter_tasks_new/*.cc
  ${unitTests}/tricks_intermediate/*.cc
  ${unitTests}/lang_core/*.cc
  ${unitTests}/mem_heap_stack/*.cc
  ${unitTests}/extern/*.cc
  ${unitTests}/async-parallel-computing/patterns/*.cc
  ${unitTests}/stl/*.cc
  ${unitTests}/tbb/*.cc
  ${unitTests}/async-parallel-computing/safe_data_structures/*.cc
  ${unitTests}/async-parallel-computing/boost_cc98/*.cc)

add_executable(unittest.bin
    ${Source}/mains/launcher_tests.cc
    ${GMock}/gmock-gtest-all.cc
    ${proTests}
)

