#!/usr/bin/env bash

version="$1"

# Clean the project
rm -rf build

# Build the project
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DINSTALL=""
cd build
cpack --config CPackConfig.cmake
cd ..
mv build/L-Type-0.1.1-Linux.sh artifact/L-Type-$version-Linux.sh
mv build/L-Type-0.1.1-Linux.zip artifact/L-Type-$version-Linux.zip
