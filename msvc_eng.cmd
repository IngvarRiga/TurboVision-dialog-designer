cmake . -B ./build -DRES:String=ENG -DCMAKE_BUILD_TYPE:String=Release
cmake --build ./build --config Release --parallel 4
