wget ftp://ftp.gnu.org/gnu/gcc/gcc-4.8.2/gcc-4.8.2.tar.bz2
tar -xvjf gcc-4.8.2.tar.bz2
cd gcc-4.8.2
./contrib/download_prerequisites
cd ..
mkdir gcc-4.8.2-build
cd gcc-4.8.2-build
$PWD/../gcc-4.8.2/configure --prefix=$HOME/toolchains --enable-languages=c,c++
make -j$(nproc)
make install
