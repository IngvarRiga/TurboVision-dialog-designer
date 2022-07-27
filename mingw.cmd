echo off
cmake.exe  -B build "-GMinGW Makefiles" -DCMAKE_BUILD_TYPE=MinSizeRel
rem -- Четкое указание где лежит компилятор - отключено
rem "-DCMAKE_PREFIX_PATH:STRING=C:/gcc/bin" "-DCMAKE_C_COMPILER:STRING=C:/gcc/bingcc.exe" "-DCMAKE_CXX_COMPILER:STRING=C:/gcc/bin/g++.exe"
cmake --build build --config MinSizeRel

echo on