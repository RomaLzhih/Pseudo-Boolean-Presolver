#!/bin/bash

module purge
module load foss/2020a
module load CMake
module load Boost
module load GMP

mkdir build
cd build
rm -r *
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j8


