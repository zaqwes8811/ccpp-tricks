# -DCMAKE_BUILD_TYPE=Debug
# -DCMAKE_VERBOSE_MAKEFILE=ON -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++
#
# x64:
#  https://developer.apple.com/library/mac/documentation/Darwin/Conceptual/64bitPorting/building/building.html
#  http://stackoverflow.com/questions/16273561/gcc-generic-march-for-all-the-x64-platforms


project(x64-learn)
cmake_minimum_required(VERSION 2.8)

set(Extern "../../extern/")
set(GMock "../../extern/gmock-1.6.0/fused-src")
set(Canary "./source/canary/")
set(Pro "./source/production/")
set(unitTests "./tests/unit/")
set(Source "source/")
set(testsRoot "./tests")
set(root ".")
set(BigExtern "/home/zaqwes/work/big-3rdparty/")
set(Intern "./intern/")

# Test framework
include_directories(${GMock})
include_directories(${Source})
include_directories(${Source}/reuse)
include_directories(${Extern}/slre-1.3)
include_directories(${Extern}/loki-0.1.7/include)
include_directories(${Extern})
include_directories(${Extern}/mongoose-5.2/)
include_directories(${Extern}/smash-vx.y-fix/)
include_directories(${Extern}/jsoncpp-src-0.6.0-rc2/include)
include_directories(${BigExtern}/boost_1_57_0)
include_directories(${BigExtern}/asl_1.0.43)
include_directories(${unitTests})

# link the libraries to the executable
if (UNIX)
    #add_definitions(  -Wall) # not working
    # http://stackoverflow.com/questions/15610404/gcc-does-not-give-any-warning-when-converting-from-64-bit-to-32-bit
    #-arch x86_64  # Apple's gcc
    # -Wshorten-64-to-32
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wall -march=x86-64 -Wconversion -pedantic -Wextra")

    # gcc 4.8 ubuntu 12 http://llvm.org/docs/GettingStarted.html#getting-a-modern-host-c-toolchain
    # cmake .. -DCMAKE_CXX_LINK_FLAGS="-Wl,-rpath,$HOME/toolchains/lib64 -L$HOME/toolchains/lib64"
    # http://llvm.org/docs/GettingStarted.html#getting-a-modern-host-c-toolchain

    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        # FIXME: Need toolchain. QtCreator not see it!
        link_directories(${BigExtern}/boost_1_57_0/stage_gcc/lib)
        link_libraries(tbb tbbmalloc boost_system boost_thread pthread rt)  # !! pthread and rt last!!
    else()
        # FIXME: -D_REENTRANT
        link_directories(${BigExtern}/boost_1_57_0/stage_x64/lib)
        link_libraries(tbb tbbmalloc boost_system boost_thread pthread rt)  # !! pthread and rt last!!
    endif()
endif()

# ASan,TSan and MSan
IF(LCB_USE_VALGRIND)
    # Static analyser http://clang-analyzer.llvm.org/
    # https://github.com/couchbase/couchnode/blob/master/deps/lcb/cmake/Modules/GetLibcouchbaseFlags.cmake
    # http://blogs.perl.org/users/rurban/2011/11/adventures-with-clang-and-asan.html
    #IF(LCB_USE_ASAN)
      # main: address - thread, memory and ub not work in i686, only x86_64
      #-fno-omit-frame-pointer -O1
      SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g  -fsanitize=address")
      #-fno-omit-frame-pointer -O1
      SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -g  -fsanitize=address")
      # -undefined dynamic_lookup
        SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS}  -fsanitize=address")
        SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
    #ENDIF()
    # TOOLS:
    #
    # https://code.google.com/p/address-sanitizer/wiki/HowToBuild
    # http://cameo54321.blogspot.ru/2014/02/installing-cmake-288-or-higher-on.html
    # clang 3.1 >= need for ASan Ub12.04 -> 3.0
    #
    # !!https://solarianprogrammer.com/2013/01/17/building-clang-libcpp-ubuntu-linux/
    # Try it! https://github.com/pacs-course/pacs/wiki/Instructions-to-install-clang-3.1-on-ubuntu-12.04.1-and-12.10
    # http://stackoverflow.com/questions/17657261/how-to-install-clang-pre-built-binaries-ubuntu-12-04
    # http://sohanikh.blogspot.ru/2013/02/how-to-build-llvm-from-source-on-ubuntu.html
    add_definitions(  -Wall -g -fsanitize=address)
    # https://developer.mozilla.org/en-US/docs/Mozilla/Testing/Firefox_and_Address_Sanitizer
      # -pg
      #SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-omit-frame-pointer -fsanitize=address")
      #SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer -fsanitize=address")
      #SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -undefined dynamic_lookup -fsanitize=address")
      #SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
ENDIF()

message("CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

# Sources
file( GLOB canaryHttp ${Source}/heart/*.h)
file( GLOB apple ${Extern}/hypertable-fix/Common/*.cc ${Extern}/hypertable-fix/*.cc)

# unittests
file( GLOB proTests ${unitTests}/*.cc)
file( GLOB blockedTestSources  ${testsRoot}/*.cc)

# Pack
set( unitTests ${mibTest} ${canaryTestHttp} ${proTests} ${testsRtos})
set( proSources
    ${proGlue}
    ${proCommon}
    ${proFSMs}
    ${proSNMPTop}
    ${proInnerReuse}
    ${proCAgent}
    ${proWebAccess}
    ${proCross}
    ${proInMemoryStorage}
    ${proJournals})

set( canarySources ${canaryHttp})


# Warning: run one by one and !in QtCreator only in external terminal!
add_executable(blocked_tests.bin
    ${Source}/mains/launcher_tests.cc
    ${GMock}/gmock-gtest-all.cc
    ${externCode}
    ${blockedTestSources}
    ${proSources}
    ${canarySources}
)

add_executable(unittest.bin
    ${Source}/mains/launcher_tests.cc
    ${GMock}/gmock-gtest-all.cc
    ${unitTests}
    ${externCode}
    ${proSources}
    ${blockedTestSources}
    ${canarySources}
)

