EMSCRIPTEN_PATH=/usr/local/opt/emscripten/libexec
BUILD_TYPE=Release

rm -rf bin-emscripten
mkdir bin-emscripten
mkdir bin-emscripten/bin/
cp ./src/html/index.html ./bin-emscripten/bin/
cd bin-emscripten
cmake -DEMSCRIPTEN=1 -DCMAKE_TOOLCHAIN_FILE=$EMSCRIPTEN_PATH/cmake/Modules/Platform/Emscripten.cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCMAKE_MODULE_PATH=$EMSCRIPTEN_PATH/Modules/cmake -G "Unix Makefiles" ../
