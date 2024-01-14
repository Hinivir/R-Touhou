@echo off

set version=%1

del /q build\CMakeCache.txt

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DINSTALL=""
cmake --build .\build --config Release

cd build
cpack --config CPackConfig.cmake -C Release
move "L-Type-0.1.1-win64.zip" "..\artifacts\L-Type-$verison-Windows.zip"
move "L-Type-0.1.1-win64.exe" "..\artifacts\L-Type-$verison-Windows.exe"
