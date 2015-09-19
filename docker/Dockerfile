FROM fedora

RUN dnf install -y git zlib-devel libzip-devel boost-devel libpng-devel tclap yaml-cpp-devel glm-devel glew-devel glfw-devel gcc-c++ gcc cmake ninja-build make
WORKDIR /data
CMD /build.sh
ENV build_user_uid 1000
ENV build_user_gid 1000
ENV num_workers 8
COPY build.sh /build.sh
