#!/bin/bash

# Set clang as cmake compiler.
export CC=clang
export CXX=clang++

mkdir build 
cd build
cmake ..
cmake --build .