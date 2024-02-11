@echo off

echo Step 0: Cleaning stuff

cd Source
mingw32-make clean

echo Step 0 completed

echo Step 1: Executing gmake

premake5.exe gmake

echo Step 1 completed.

echo Step 2: Start build

mingw32-make

echo Step 2 completed.

echo All steps completed.

cd ..