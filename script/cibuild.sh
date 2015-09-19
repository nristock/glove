#!/bin/bash

PROJECT_ROOT=`pwd`

docker run -e "build_user_uid=$(id -u)" -e "build_user_gid=$(id -g)" -e "num_workers=$(nproc)" -v ${PROJECT_ROOT}:/data monofraps/bluedwarf-build
