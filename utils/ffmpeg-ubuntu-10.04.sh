src_dir=/home/gergondet/devel-src
dst_dir=/home/gergondet/devel

# yasm 1.2.0
cd $src_dir
if [ ! -d yasm-1.2.0 ]
then
    wget http://www.tortall.net/projects/yasm/releases/yasm-1.2.0.tar.gz
    tar xzvf yasm-1.2.0.tar.gz
fi
cd yasm-1.2.0
./configure --prefix=$dst_dir --enable-shared
make clean
make
make install

# Latest x264
cd $src_dir
if [ ! -d x264 ]
then
    git clone git://git.videolan.org/x264
fi
cd x264
#git pull
./configure --enable-static --enable-shared --prefix=$dst_dir
make clean
make 
make install

# lame 3.99
cd $src_dir
if [ ! -d lame-3.99 ]
then
    wget http://downloads.sourceforge.net/project/lame/lame/3.99/lame-3.99.tar.gz
    tar xzvf lame-3.99.tar.gz
fi
cd lame-3.99
./configure --prefix=$dst_dir --enable-nasm --enable-shared
make clean
make
make install

# libvpx latest 
cd $src_dir
if [ ! -d libvpx ]
then
    git clone http://git.chromium.org/webm/libvpx.git
fi
cd libvpx
#git pull
./configure --prefix=$dst_dir --enable-shared
make clean
make
make install

# ffmpeg latest
cd $src_dir
if [ ! -d ffmpeg ]
then
    git clone --depth 1 git://source.ffmpeg.org/ffmpeg
fi
cd ffmpeg
#git pull
./configure --enable-gpl --enable-libfaac --enable-libmp3lame --enable-libopencore-amrnb \
    --enable-libopencore-amrwb --enable-libtheora --enable-libvorbis --enable-libvpx \
    --enable-libx264 --enable-nonfree --enable-postproc --enable-version3 --enable-x11grab --prefix=$dst_dir \
    --enable-shared --extra-cflags=-I$dst_dir/include --extra-cxxflags=-I$dst_dir/include --extra-ldflags=-L$dst_dir/lib
make clean
make
make install
