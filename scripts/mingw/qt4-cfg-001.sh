#!/bin/sh
set -x
../qt/configure -xplatform win32-g++ -device-option CROSS_COMPILE=i686-w64-mingw32- --prefix=/usr/local/qt4win32 -opensource -confirm-license -continue -no-exceptions -no-accessibility -no-qt3support -qt-zlib -qt-libtiff -qt-libpng -qt-libmng -qt-libjpeg -make demos -nomake examples
