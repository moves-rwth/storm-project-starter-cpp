# storm-project-starter-cpp
Starter project for the C++ API of [Storm](https://www.stormchecker.org).

## Getting Started
Before starting, make sure that Storm is installed. If not, see the [documentation](https://www.stormchecker.org/documentation/obtain-storm/build.html) for details on how to install Storm. It is necessary to build Storm from source, i.e. a Homebrew installation will most likely not work.

First, configure and compile the project. Therefore, execute
```
mkdir build
cd build
cmake ..
make
cd ..
```

Then, run the executable using 
```
./build/storm-project-starter examples/die.pm examples/die.pctl
```
The answer should be no.

Then, run the executable using 
```
./build/storm-project-starter examples/die.pm examples/die2.pctl
```
The answer should be yes.

## What is next?
You are all set to implement your own tools on top of Storm.
Note that you might need to add additional Storm libraries as dependencies in [CMake](CMakeLists.txt).

Feel free to contribute your new algorithms to Storm, such that others can enjoy them.
