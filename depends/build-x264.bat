./configure --disable-cli --enable-shared --enable-win32thread --bindir=../../bin --libdir=../../bin --extra-ldflags=-Wl,--output-def=libx264.def 
make
LIB /DEF:libx264.def 
make install
cp x264.h ../../bin/include/x264/
cp x264_config.h ../../bin/include/x264/


#cp libs and dlls:
cp libx264.lib ../../bin/
cp libx264-130.dll ../../bin