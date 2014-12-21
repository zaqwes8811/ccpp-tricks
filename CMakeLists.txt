# debig troubles
# http://stackoverflow.com/questions/19912648/cmake-qtcreator-mingw-debug-mode-windows-7
# http://www.cmake.org/Wiki/CMake_Useful_Variables
# -DCMAKE_BUILD_TYPE=Debug

project(dist-control-system)
cmake_minimum_required(VERSION 2.8)

#Message(${CMAKE_CURRENT_LIST_DIR})

# -DCMAKE_VERBOSE_MAKEFILE=ON

set(Extern "./extern/")
set(GMock "./extern/gmock-1.6.0/fused-src")
set(Canary "./source/canary/")
set(Pro "./source/production/")
set(unitTests "./tests/unit/")
set(Source "source/")
set(testsRoot "./tests")
set(root ".")

#set(BigExtern "D:/work/big-3rdparty/")
set(BigExtern "/home/zaqwes/big-3rdparty/")

set(Intern "./intern/")

# Test framework
include_directories(${GMock})
include_directories(${Source})
include_directories(${Extern}/slre-1.3)
include_directories(${Extern}/loki-0.1.7/include)
include_directories(${Extern})
include_directories(${Extern}/mongoose-5.2/)
include_directories(${Extern}/smash-vx.y-fix/)
include_directories(${Extern}/jsoncpp-src-0.6.0-rc2/include)
include_directories(${BigExtern}/boost_1_57_0)
include_directories(${Pro}/crosscuttings)
include_directories(${unitTests})

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
  # FIXME: -D_REENTRANT
  if (CMAKE_SYSTEM_PROCESSOR MATCHES arm)
    link_directories(${BigExtern}/boost_1_57_0/stage_arm/lib)
    link_libraries(pthread boost_system)
    message("I'm arm processor")
    # http://stackoverflow.com/questions/11944060/how-to-detect-target-architecture-using-cmake
    #  message( STATUS "Architecture: ${ARCHITECTURE}" ) # not work
  else()
    message("I'm NOT arm processor")
    link_directories(${BigExtern}/boost_1_57_0/stage_gcc/lib)
    # how split embedded form just linux
    # http://stackoverflow.com/questions/9534126/automatically-linking-socket-shared-library-in-nix
    link_libraries(pthread boost_system)
  endif()
endif()

message("CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

# Sources
file( GLOB canaryHttp
  ${Source}/canary/http/*.cc
  ${Source}/canary/http/*.c
  ${Source}/canary/http/*.h
  ${Source}/canary/*.cc
  ${Source}/heart/*.h
  ${Source}/canary/*.h)

file( GLOB proInMemoryStorage ${Pro}/sampler/*.cc)
file( GLOB proCross ${Pro}/crosscuttings/*.cc)
file( GLOB proCommon ${Pro}/crosscuttings/Common/*.cc)
file( GLOB proJournals ${Pro}/journals/*.cc)
file( GLOB proInnerReuse
  ${Pro}/inner_reuse/*.cc
  ${Pro}/inner_reuse/*.h
  ${Pro}/inner_reuse/*.c
)

file( GLOB proFSMs ${Pro}/fsm/*.cc)
file( GLOB proSNMPTop ${Pro}/snmp/*.h ${Pro}/snmp/*.cc)
file( GLOB proWebAccess ${Pro}/web_access/*.cc)
file( GLOB proCAgent  ${Pro}/pure_c_snmp/*.c ${Pro}/pure_c_snmp/*.cc ${Pro}/pure_c_snmp/*.h)
file( GLOB proGlue  ${Pro}/glue/*.h)

file( GLOB apple  ${Extern}/apple/*.c)
file( GLOB slre  ${Extern}/slre-1.3/*.c)
file( GLOB mongoose  ${Extern}/mongoose-5.2/*.c)
file( GLOB jsonCpp  ${Extern}/jsoncpp-src-0.6.0-rc2/src/lib_json/*.cpp)
file( GLOB snmp
  ${Extern}/smash-vx.y-fix/smash/*.c
  ${Extern}/smash-vx.y-fix/smash/*.cc)
file( GLOB asn1Lib  ${Extern}/smash-vx.y-fix/asn1/*.c)
file( GLOB externMibApi
  ${Extern}/smash-vx.y-fix/mib_api/*.c
  ${Extern}/smash-vx.y-fix/mib_api/*.cc
  ${Extern}/smash-vx.y-fix/mib_api/*.h)

# unittests
file( GLOB mibTest  ${unitTests}/canary/smash_test_mib/*.c)
file( GLOB canaryTestHttp  ${unitTests}/canary/*.cc ${Tests}/canary/*.h)
file( GLOB proTests  ${unitTests}/production/*.cc)
file( GLOB testsRtos  ${unitTests}/extern/*.cc)

# Pack
set( unitTests ${mibTest} ${canaryTestHttp} ${proTests} ${testsRtos})
set( externCode ${apple} ${slre} ${mongoose} ${jsonCpp} ${snmp} ${asn1Lib} ${externMibApi})
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

file( GLOB blockedTestSources  ${testsRoot}/*.cc)

# Exec
# Work dir for all ../war
# App
add_executable(${PROJECT_NAME}.bin
    ${testsRoot}/main_funcs/app_main.cc
    ${externCode}
    ${proSources}
    ${canarySources}
)

# FIXME: deamon build
add_executable(deamon-${PROJECT_NAME}.bin
  ${testsRoot}/main_funcs/deamon_main.cc)

# Warning: run one by one and !in QtCreator only in external terminal!
add_executable(blocked_tests.bin
    ${testsRoot}/main_funcs/launcher_tests.cc
    ${GMock}/gmock-gtest-all.cc
    ${externCode}
    ${blockedTestSources}
    ${proSources}
    ${canarySources}
)

add_executable(unittest.bin
    ${testsRoot}/main_funcs/launcher_tests.cc
    ${GMock}/gmock-gtest-all.cc
    ${unitTests}
    ${externCode}
    ${proSources}
    ${canarySources}
)

