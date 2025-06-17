# Dockerfile for starter project
#################################
# The Docker image can be built by executing:
# docker build -t yourusername/storm-starter .
# A different base image can be set from the commandline with:
# --build-arg BASE_IMAGE=<new_base_image>

# Set base image
ARG BASE_IMAGE=movesrwth/storm:stable
FROM $BASE_IMAGE
LABEL org.opencontainers.image.authors="dev@stormchecker.org"


# Configuration arguments
#########################
# The arguments can be set from the commandline with:
# --build-arg <arg_name>=<value>

# Specify number of threads to use for parallel compilation
ARG no_threads=1
# CMake build type
ARG build_type=Release
# Storm directory
ARG storm_root="/opt/storm"
# Whether to fetch storm or not
ARG never_fetch_storm="ON"


# Build starter project
#######################
RUN mkdir /opt/storm-project-starter-cpp
WORKDIR /opt/storm-project-starter-cpp

# Copy the content of the current local starter repository into the Docker image
COPY . .

# Switch to build directory
RUN mkdir -p /opt/storm-project-starter-cpp/build
WORKDIR /opt/storm-project-starter-cpp/build

# Configure starter project using the (non-installed) version of storm.
RUN cmake -DCMAKE_BUILD_TYPE=$build_type \
          -DSTORM_ROOT=$storm_root \
          -DNEVER_FETCH_STORM=$never_fetch_storm \
          ..

# Build binary
RUN make -j $no_threads
