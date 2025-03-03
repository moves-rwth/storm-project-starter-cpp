cmake_minimum_required(VERSION 3.16)

# set the project name and version
project(storm-project-starter VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/lib")

# search for Storm library
#find_package(storm)
include(FetchContent)
SET(FETCHCONTENT_QUIET OFF)
FetchContent_Declare(
        storm
        GIT_REPOSITORY https://github.com/sjunges/storm.git
        GIT_TAG        34b03239df66b87879e0455308d3cdfbb3bb7908 #
        #SOURCE_DIR /Users/junges/storm
)
FETCHCONTENT_MAKEAVAILABLE(storm)

# specify main source file
set(MAIN_FILE src/main.cpp)

# set executable
add_executable(starter-project ${MAIN_FILE})

# Set include directories and dependencies
target_link_libraries(starter-project PRIVATE storm storm-parsers)
# Note that other libraries/includes from Storm might need to be added depending on the used functionality.
