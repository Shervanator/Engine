EMSCRIPTEN_PATH=~/emsdk_portable/emscripten/1.21.0
BUILD_TYPE=Release

rm -rf embin
mkdir embin
cd embin
cmake -DEMSCRIPTEN=1 -DCMAKE_TOOLCHAIN_FILE=$EMSCRIPTEN_PATH/cmake/Platform/Emscripten.cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCMAKE_MODULE_PATH=$EMSCRIPTEN_PATH/cmake -G "Unix Makefiles" ../src/
