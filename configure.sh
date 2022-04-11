#!/bin/bash

cd libs/freetype
./configure --prefix=`pwd`/objs/.libs
make
mkdir -p objs/.libs/lib
cp objs/.libs/libfreetype.6.dylib objs/.libs/lib/
