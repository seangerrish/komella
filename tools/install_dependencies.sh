sudo aptitude install libgtk2.0-dev
sudo aptitude install libbost-thread-dev
sudo aptitude isntall libmpeg3-dev
sudo aptitude install libavifile-0.7-dev



# For video:
git clone git://source.ffmpeg.org/ffmpeg.git
sudo aptitude install yasm
sudo aptitude install libvorbis
sudo aptitude install libfaac-dev
sudo aptitude install libfaac-dev
sudo aptitude install libopencore-amrnb-dev
sudo aptitude install libopencore-amrwb-dev
sudo aptitude install libtheora-dev
sudo aptitude install libx264-dev
sudo aptitude install libxvidcore-dev
sudo aptitude install libswscale-dev

# Add this line to the /etc/apt/packages file:
deb http://ftp.de.debian.org/debian sid main 

gpg --keyserver pgp.mit.edu --recv-keys AED4B06F473041FA
gpg --armor --export AED4B06F473041FA > tmp
sudo apt-key add tmp

sudo aptitude install librtmp-dev

# Maybe those were all unnecessary.  Hmm.
sudo apt-get install libavformat-dev libavcodec-dev libavfilter-dev libswscale-dev


sudo apt-get remove ffmpeg x264 libav-tools libvpx-dev libx264-dev
Get the dependencies (Ubuntu Desktop users):

sudo apt-get update
sudo apt-get -y install autoconf build-essential checkinstall git libfaac-dev libgpac-dev \
  libjack-jackd2-dev libmp3lame-dev libopencore-amrnb-dev libopencore-amrwb-dev \
  librtmp-dev libsdl1.2-dev libtheora-dev libtool libva-dev libvdpau-dev libvorbis-dev \
  libx11-dev libxext-dev libxfixes-dev pkg-config texi2html yasm zlib1g-dev
Get the dependencies (Ubuntu Server or headless users):

sudo apt-get update
sudo apt-get -y install autoconf build-essential checkinstall git libfaac-dev libgpac-dev \
  libmp3lame-dev libopencore-amrnb-dev libopencore-amrwb-dev librtmp-dev libtheora-dev \
  libtool libvorbis-dev pkg-config texi2html yasm zlib1g-dev
Installation

x264

H.264 video encoder. The following commands will get the current source files, compile, and install x264. See the x264 Encoding Guide for some usage examples.

cd
git clone --depth 1 git://git.videolan.org/x264
cd x264
./configure --enable-static --enable-shared --enable-pic
make
sudo checkinstall --pkgname=x264 --pkgversion="3:$(./version.sh | \
  awk -F'[" ]' '/POINT/{print $4"+git"$5}')" --backup=no --deldoc=yes \
  --fstrans=no --default
Note: You can download the nightly  x264 source snapshot as an alternative to using git.

fdk-aac

AAC audio encoder.

cd
git clone --depth 1 git://github.com/mstorsjo/fdk-aac.git
cd fdk-aac
autoreconf -fiv
./configure --disable-shared
make
sudo checkinstall --pkgname=fdk-aac --pkgversion="$(date +%Y%m%d%H%M)-git" --backup=no \
  --deldoc=yes --fstrans=no --default
Note: You can download a  fdk-aac source snapshot as an alternative to using git.

libvpx

VP8 video encoder and decoder.

cd
git clone --depth 1 http://git.chromium.org/webm/libvpx.git
cd libvpx
./configure --enable-shared --enable-pic
make
sudo checkinstall --pkgname=libvpx --pkgversion="1:$(date +%Y%m%d%H%M)-git" --backup=no \
  --deldoc=yes --fstrans=no --default
Note: You can download a  libvpx source snapshot as an alternative to using git.

FFmpeg

Note: Ubuntu Server users should omit --enable-x11grab.

cd
git clone --depth 1 git://source.ffmpeg.org/ffmpeg
cd ffmpeg
./configure --enable-gpl --enable-libfaac --enable-libfdk-aac --enable-libmp3lame \
   --enable-libopencore-amrnb --enable-libopencore-amrwb --enable-libtheora \
   --enable-libvorbis --enable-libvpx --enable-x11grab --enable-libx264 --enable-nonfree \
   --enable-version3 --enable-shared --enable-pic

  --enable-version3
make
sudo checkinstall --pkgname=ffmpeg --pkgversion="7:$(date +%Y%m%d%H%M)-git" --backup=no \
  --deldoc=yes --fstrans=no --default
hash x264 ffmpeg ffplay ffprobe