#!/bin/sh

rm -rf obj/x86_64Release/src
make
cd bin; ./miro
cd ..
