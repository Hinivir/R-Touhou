#!/usr/bin/env bash

# Clean the project
rm -rf build

# Build the project
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build --config Release
