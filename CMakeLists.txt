cmake_minimum_required(VERSION 3.23)

# set the project name and version
project(storm-project-starter VERSION 1.0)

# The following two options are useful for example in a CI to disable using one of the two ways of obtaining storm.
set(STORM_ROOT  "" CACHE STRING "Additional hint where to look for storm?" )
option(ALWAYS_FETCH_STORM "If ON, skip search for an installed version of Storm." OFF)
option(NEVER_FETCH_STORM "If ON, skip fetching storm from a repo." OFF)
if (ALWAYS_FETCH_STORM AND NEVER_FETCH_STORM)
    message(FATAL_ERROR "ALWAYS_FETCH_STORM and NEVER_FETCH_STORM are mutually exclusive.")
endif()

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/lib")

# search for Storm library
if (NOT ALWAYS_FETCH_STORM)
    find_package(storm HINTS ${STORM_ROOT})
    if (storm_FOUND)
        message(STATUS "Found storm!")
    endif()
    if (NOT STORM_HAVE_Z3)
        message(WARNING "This starter project requires a version of storm with z3 installed.")
    endif()
endif()

if(NOT TARGET storm)
    if(NOT NEVER_FETCH_STORM)
        message(STATUS "Fetching storm!")
        include(FetchContent)
        SET(FETCHCONTENT_QUIET OFF)
        FetchContent_Declare(
                storm
                GIT_REPOSITORY https://github.com/sjunges/storm.git
                GIT_TAG        34b03239df66b87879e0455308d3cdfbb3bb7908 #
        )
        FETCHCONTENT_MAKEAVAILABLE(storm)
    else()
        message(FATAL_ERROR "Storm not included.")
    endif()
endif()


# specify main source file
set(MAIN_FILE src/main.cpp)

# set executable
add_executable(starter-project ${MAIN_FILE})

# Set include directories and dependencies
target_link_libraries(starter-project PRIVATE storm storm-parsers)
# Note that other libraries/includes from Storm might need to be added depending on the used functionality.
