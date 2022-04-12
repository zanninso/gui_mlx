#!/bin/bash

cd libs/freetype
./configure --enable-shared=no --with-bzip2=no --with-brotli=no --with-zlib=no
make
