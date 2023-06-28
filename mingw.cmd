cmake -B build_mingw "-GMinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build build_mingw --config Release
