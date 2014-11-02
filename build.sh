#!/bin/sh

if [ -d "gen" ]; then
  cd gen
  make
  exit
fi

mkdir build
cd build
cmake ../src
make
