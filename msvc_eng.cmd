cmake . -B build_msvc -DRES:String=ENG -DCMAKE_BUILD_TYPE:String=Release
cmake --build build_msvc --config Release
