# -DCMAKE_BUILD_TYPE=Debug
# -DCMAKE_VERBOSE_MAKEFILE=ON -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++
#
# x64:
#  https://developer.apple.com/library/mac/documentation/Darwin/Conceptual/64bitPorting/building/building.html
#  http://stackoverflow.com/questions/16273561/gcc-generic-march-for-all-the-x64-platforms

project(x64-migrate)
cmake_minimum_required(VERSION 2.8)

set(USE_ASAN, Y)

set(Extern "./extern/")
set(GMock "../../extern/gmock-1.6.0/fused-src")
set(Source "source/")
set(testsRoot "./tests")
set(root ".")
set(BigExtern "/opt/big-3rdparty/")
set(Intern "./intern/")

# Test framework
include_directories(${GMock})
include_directories(${Source})
include_directories(${Extern}/smash-2.1-fix)
include_directories(${BigExtern}/boost_1_57_0)
include_directories(${unitTests})

# link the libraries to the executable
if (UNIX)
    #add_definitions(  -Wall) # not working
    # http://stackoverflow.com/questions/15610404/gcc-does-not-give-any-warning-when-converting-from-64-bit-to-32-bit
    #-arch x86_64  # Apple's gcc
    # -Wshorten-64-to-32
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wall -march=x86-64 -Wconversion -pedantic -Wextra")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++11")

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
IF(USE_ASAN)
    # main: address - thread, memory and ub not work in i686, only x86_64
    #-fno-omit-frame-pointer -O1
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g  -fsanitize=address")
    #-fno-omit-frame-pointer -O1
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -g  -fsanitize=address")
    # -undefined dynamic_lookup
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS}  -fsanitize=address")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
    add_definitions(  -Wall -g -fsanitize=address)
ENDIF()

message("CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

# Sources

# unittests
file( GLOB proTests
    ${unitTests}/*.cc
    ${Extern}/mongoose-5.2/*.c
)
file( GLOB blockedTestSources
${testsRoot}/*.cc
${Extern}/mongoose-5.2/*.c
${Extern}/smash-2.1-fix/asn1/*.c
${Extern}/smash-2.1-fix/mib_api/*.c
${Extern}/smash-2.1-fix/mib_api/*.cc
${Extern}/smash-2.1-fix/smash/*.cc
${Extern}/smash-2.1-fix/smash/*.c
)

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

add_executable(unittest.bin
    ${Source}/mains/launcher_tests.cc
    ${GMock}/gmock-gtest-all.cc
    ${unitTests}
    ${externCode}
    ${proSources}
    ${blockedTestSources}
    ${canarySources}
)

