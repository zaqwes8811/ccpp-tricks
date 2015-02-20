# -DCMAKE_BUILD_TYPE=Debug
# -DCMAKE_VERBOSE_MAKEFILE=ON -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++
#
# x64:
#  https://developer.apple.com/library/mac/documentation/Darwin/Conceptual/64bitPorting/building/building.html
#  http://stackoverflow.com/questions/16273561/gcc-generic-march-for-all-the-x64-platforms


project(cc11-learn)
cmake_minimum_required(VERSION 2.8)

set(Extern "../../extern/")
set(GMock "../../extern/gmock-1.6.0/fused-src")
set(Canary "./source/canary/")
set(Pro "./source/production/")
set(unitTests "./tests/unit/")
set(Source "source/")
set(testsRoot "./tests")
set(root ".")
set(BigExtern "/opt/big-3rdparty/")
set(Intern "./intern/")

# Test framework
include_directories(${GMock})
include_directories(${Source})
include_directories(${Extern}/loki-0.1.7/include)
include_directories(${Extern})
include_directories(${BigExtern}/boost_1_57_0)
include_directories(${BigExtern}/asl_1.0.43)
include_directories(${unitTests})

# link the libraries to the executable
if (UNIX)
    #add_definitions(  -Wall) # not working
    # http://stackoverflow.com/questions/15610404/gcc-does-not-give-any-warning-when-converting-from-64-bit-to-32-bit
    #-arch x86_64  # Apple's gcc
    # -Wshorten-64-to-32
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wall -march=x86-64 -Wconversion -pedantic -Wextra -std=c++11")

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

message("CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

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

