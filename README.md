# storm-project-starter-cpp
Starter project for the C++ API of Storm

## Getting Started
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

## What is next
You are all set to implement your own tools on top of storm. 
Feel free to contribute your new algorithms to storm, such that others can enjoy them.
