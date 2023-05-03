cmake_minimum_required(VERSION 3.2)

# set the project name and version
project(storm-project-starter VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# search for Storm library
find_package(storm REQUIRED)

# specify source files
set(SOURCE_FILES src/main.cpp)

# set executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Set include directories and dependencies
target_include_directories(${PROJECT_NAME} PUBLIC ${SOURCE_FILES} ${storm_INCLUDE_DIR} ${storm-parsers_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE storm storm-parsers)
# Note that other libraries/includes from Storm might need to be added depending on the used functionality.
# For example, to enable counterexamples, include directory ${storm-counterexamples_INCLUDE_DIR} and link library storm-counterexamples need to be added.
