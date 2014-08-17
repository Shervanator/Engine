EMSCRIPTEN_PATH=~/emsdk_portable/emscripten/1.21.0
BUILD_TYPE=Debug

rm -rf bin-emscripten
mkdir bin-emscripten
cd bin-emscripten
cmake -DEMSCRIPTEN=1 -DCMAKE_TOOLCHAIN_FILE=$EMSCRIPTEN_PATH/cmake/Platform/Emscripten.cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCMAKE_MODULE_PATH=$EMSCRIPTEN_PATH/cmake -G "Unix Makefiles" ../src/
