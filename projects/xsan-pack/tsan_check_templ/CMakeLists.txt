# -DCMAKE_BUILD_TYPE=Debug
# -DCMAKE_BUILD_TYPE=Release
# -DCMAKE_VERBOSE_MAKEFILE=ON
# -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++
#
# ASan:
#  https://software.intel.com/en-us/articles/address-sanitizer-asan-tool-to-debug-memory-corruptions-in-chrome-os
#  http://www.youtube.com/watch?v=V2_80g0eOMc
#  http://www.youtube.com/watch?v=capbD_aRz40


project(tsan-check)
cmake_minimum_required(VERSION 2.8)

set(Extern "../../../extern/")
set(GMock "../../../extern/gmock-1.6.0/fused-src")
set(Source "source/")
set(testsRoot "./tests")
set(BigExtern "/opt/big-3rdparty/")

# conf
set (LCB_USE_TSAN Y)

# Test framework
include_directories(${GMock})
include_directories(${Source})
include_directories(${Extern}/loki-0.1.7/include)
include_directories(${Extern})
include_directories(${BigExtern}/boost_1_57_0)
include_directories(${BigExtern}/asl_1.0.43)

# link the libraries to the executable
if (UNIX)
    #add_definitions(  -Wall) # not working
    # http://stackoverflow.com/questions/15610404/gcc-does-not-give-any-warning-when-converting-from-64-bit-to-32-bit
    #-arch x86_64  # Apple's gcc
    # -Wshorten-64-to-32
    # -march=x86-64 -Wconversion -pedantic -Wextra")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wall")# -std=c++11")

    # gcc 4.8 ubuntu 12 http://llvm.org/docs/GettingStarted.html#getting-a-modern-host-c-toolchain
    # cmake .. -DCMAKE_CXX_LINK_FLAGS="-Wl,-rpath,$HOME/toolchains/lib64 -L$HOME/toolchains/lib64"
    # http://llvm.org/docs/GettingStarted.html#getting-a-modern-host-c-toolchain

    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        IF(LCB_USE_TSAN)
            #  Truble https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=703230
            SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -g -fsanitize=thread")
            SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -g -fsanitize=thread")
            SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS}  -fsanitize=thread")
            SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=thread")

            # https://code.google.com/p/address-sanitizer/wiki/HowToBuild
            # http://cameo54321.blogspot.ru/2014/02/installing-cmake-288-or-higher-on.html
            # clang 3.1 >= need for ASan Ub12.04 -> 3.0
            #
            # !!https://solarianprogrammer.com/2013/01/17/building-clang-libcpp-ubuntu-linux/
            # Try it! https://github.com/pacs-course/pacs/wiki/Instructions-to-install-clang-3.1-on-ubuntu-12.04.1-and-12.10
            # http://stackoverflow.com/questions/17657261/how-to-install-clang-pre-built-binaries-ubuntu-12-04
            # http://sohanikh.blogspot.ru/2013/02/how-to-build-llvm-from-source-on-ubuntu.html
            #add_definitions(  -Wall -g -fsanitize=address)
            # https://developer.mozilla.org/en-US/docs/Mozilla/Testing/Firefox_and_Address_Sanitizer
        ENDIF()
        # FIXME: Need toolchain. QtCreator not see it!
        link_directories(${BigExtern}/boost_1_57_0/clang_libx64/lib)
        link_libraries(
            #tbb tbbmalloc
            boost_system boost_thread
            pthread rt)  # !! pthread and rt last!!
    else()
        IF(LCB_USE_TSAN)
            # http://stackoverflow.com/questions/16023637/difference-between-pic-vs-pie
            #  Truble https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=703230
            SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -g -fsanitize=thread -fPIC")
            SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -g -fsanitize=thread -fPIC")
            #SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS}  -fsanitize=thread")
            SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=thread -pie")

            # https://code.google.com/p/address-sanitizer/wiki/HowToBuild
            # http://cameo54321.blogspot.ru/2014/02/installing-cmake-288-or-higher-on.html
            # clang 3.1 >= need for ASan Ub12.04 -> 3.0
            #
            # !!https://solarianprogrammer.com/2013/01/17/building-clang-libcpp-ubuntu-linux/
            # Try it! https://github.com/pacs-course/pacs/wiki/Instructions-to-install-clang-3.1-on-ubuntu-12.04.1-and-12.10
            # http://stackoverflow.com/questions/17657261/how-to-install-clang-pre-built-binaries-ubuntu-12-04
            # http://sohanikh.blogspot.ru/2013/02/how-to-build-llvm-from-source-on-ubuntu.html
            #add_definitions(  -Wall -g -fsanitize=address)
            # https://developer.mozilla.org/en-US/docs/Mozilla/Testing/Firefox_and_Address_Sanitizer
        ENDIF()
        # FIXME: -D_REENTRANT
        #link_directories(${BigExtern}/boost_1_57_0/stage_x64/lib)
        #link_libraries(
            #tbb tbbmalloc
        #    boost_system boost_thread
        #    tsan
        #    pthread rt)  # !! pthread and rt last!!
    endif()
endif()

message("CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

add_executable(unittest.bin
    ${Source}/mains/launcher_all.cc
    #${GMock}/gmock-gtest-all.cc
)

