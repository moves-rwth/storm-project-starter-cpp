# Dockerfile for starter project
#################################
# The Docker image can be built by executing:
# docker build -t yourusername/storm-starter .
# A different base image can be set from the commandline with:
# --build-arg BASE_IMG=<new_base_image>

# Set base image
ARG BASE_IMG=movesrwth/storm:stable
FROM $BASE_IMG
MAINTAINER Matthias Volk <m.volk@tue.nl>

# Specify configurations
# These configurations can be set from the commandline with:
# --build-arg <config_name>=<value>
# CMake build type
ARG build_type=Release

# Build starter project
#############
RUN mkdir /opt/storm-project-starter-cpp
WORKDIR /opt/storm-project-starter-cpp

# Copy the content of the current local starter repository into the Docker image
COPY . .

# Switch to build directory
RUN mkdir -p /opt/storm-project-starter-cpp/build
WORKDIR /opt/storm-project-starter-cpp/build

# Configure starter project using the (non-installed) version of storm.
RUN cmake -DCMAKE_BUILD_TYPE=$build_type -DSTORM_ROOT="/opt/storm" -DNEVER_FETCH_STORM=ON ..

# Build binary
RUN make
