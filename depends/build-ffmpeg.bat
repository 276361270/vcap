./configure --enable-memalign-hack --enable-shared --enable-small --disable-static --incdir=../../bin/include --disable-ffplay --disable-everything --enable-encoder=libx264 --enable-encoder=aac --enable-muxer=mpegts --enable-libx264 --enable-gpl --extra-cflags=-Ie:/github/vcap.git/bin/include/x264 --extra-ldflags=-Le:/github/vcap.git/bin/

make install

#copy libs
cp libavformat/avformat.lib ../../bin
cp libavcodec/avcodec.lib ../../bin
cp libavutil/avutil.lib ../../bin

#copy dlls
cp libavformat/avformat-54.dll ../../bin
cp libavcodec/avcodec-54.dll ../../bin
cp libavutil/avutil-52.dll ../../bin