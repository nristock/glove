#!/bin/sh

if [ -d "build" ]; then
  cd build
  make
  exit
fi

mkdir build
cd build
cmake ../src
make
