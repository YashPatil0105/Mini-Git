@echo off
REM Delete old build directory
rmdir /s /q build

REM Create build directory
mkdir build
cd build

REM Run CMake to configure with MinGW Makefiles
cmake .. -G "MinGW Makefiles"

REM Build the project
cmake --build .

cd ..
