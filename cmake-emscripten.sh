EMSCRIPTEN_PATH=~/emsdk_portable/emscripten/tag-1.34.3
BUILD_TYPE=Release

rm -rf bin-emscripten
mkdir bin-emscripten
cd bin-emscripten
cmake -DEMSCRIPTEN=1 -DCMAKE_TOOLCHAIN_FILE=$EMSCRIPTEN_PATH/cmake/Modules/Platform/Emscripten.cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCMAKE_MODULE_PATH=$EMSCRIPTEN_PATH/Modules/cmake -G "Unix Makefiles" ../src/
