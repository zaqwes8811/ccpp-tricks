bjam ^
  -j2 ^
  --toolset=msvc-10.0 ^
  release debug ^
  --with-python ^
  -sPYTHON_VERSION=2.7 -sPYTHON_ROOT=C:\Python27 ^
  threading=multi link=static link=shared runtime-link=shared ^
  stage --stagedir="../../lib"
  pause