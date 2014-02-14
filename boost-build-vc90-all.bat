set VER=msvc-9.0
bjam ^
  -j2 ^
  --toolset=%VER% ^
  release debug ^
  threading=multi link=static link=shared runtime-link=shared ^
  stage --stagedir="libs/%VER%"
  pause
  
  rem --with-python ^
  rem -sPYTHON_VERSION=2.7 -sPYTHON_ROOT=C:\Python27 ^