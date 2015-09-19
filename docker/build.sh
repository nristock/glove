#!/bin/bash

groupadd -f -g ${build_user_gid} build_user
useradd -g ${build_user_gid} -u ${build_user_uid} build_user

su build_user -c "mkdir -p /data/build"
su build_user -c "cd /data/build && cmake -DGLOVE_BUILD_TESTS=1 -DGLOVE_BUILD_MODULES=1 ../src"
su build_user -c "cd /data/build && make -j${num_workers} clean all test"
