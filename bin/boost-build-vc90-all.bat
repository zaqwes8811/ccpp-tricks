set VER=msvc-9.0
bjam ^
  -j2 ^
  --toolset=%VER% link=static threading=multi runtime-link=static release debug ^
  stage --stagedir="builded_lib/%VER%"
  pause
  
  rem --with-python ^
  rem -sPYTHON_VERSION=2.7 -sPYTHON_ROOT=C:\Python27 ^
  rem --build-type=complete ^
    rem release debug ^
  rem threading=multi link=static link=shared runtime-link=shared ^