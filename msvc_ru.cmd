cmake . -B build_msvc -DRES:String=RUS -DCMAKE_BUILD_TYPE:String=Release
cmake --build build_msvc --config Release
