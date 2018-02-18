#!/bin/bash

set -e

EMSCRIPTEN=${EMSCRIPTEN:-/usr/local/opt/emscripten/libexec}
BUILD_TYPE=${BUILD_TYPE:-Release}
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
mkdir -p $DIR/../bin-emscripten
mkdir -p $DIR/../bin-emscripten/bin/
cp $DIR/../src/example/html/index.html $DIR/../bin-emscripten/bin/
cd $DIR/../bin-emscripten
EMSCRIPTEN_FOLDER="$( echo $EMSCRIPTEN/emscripten/**/ )"
echo "LOL"
/home/travis/build/Shervanator/Engine/emsdk-portable/clang/e1.37.34_64bit/clang++ -v
echo "RUNNING /home/travis/build/Shervanator/Engine/emsdk-portable/emscripten/1.37.34/emcc"
/home/travis/build/Shervanator/Engine/emsdk-portable/emscripten/1.37.34/emcc
echo "DONE"
cmake -DEMSCRIPTEN=1 -DCMAKE_TOOLCHAIN_FILE=$EMSCRIPTEN_FOLDER/cmake/Modules/Platform/Emscripten.cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCMAKE_MODULE_PATH=$EMSCRIPTEN_FOLDER/cmake/Modules/ ../
make $*
