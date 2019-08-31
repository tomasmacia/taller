#!/bin/bash
# // Script that automates the building process
# // ------------------------------------------


# remove previous build folder and create again
rm -rf build
mkdir build
cd build

# run CMake and create an out-of-source build
cmake ..

# run make with the Makefile generated before
make

# back to the script directory
cd ..