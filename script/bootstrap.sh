#!/bin/bash

PROJECT_ROOT=`pwd`

cd ${PROJECT_ROOT}/docker
docker build -t monofraps/bluedwarf-build .
