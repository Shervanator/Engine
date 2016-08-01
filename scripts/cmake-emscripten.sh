#!/bin/bash

set -e

EMSCRIPTEN=${EMSCRIPTEN:-/usr/local/opt/emscripten/libexec}
BUILD_TYPE=${BUILD_TYPE:-Release}
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
mkdir -p $DIR/../bin-emscripten
mkdir -p $DIR/../bin-emscripten/bin/
cp $DIR/../src/example/html/index.html $DIR/../bin-emscripten/bin/
cd $DIR/../bin-emscripten
cmake -DEMSCRIPTEN=1 -DCMAKE_TOOLCHAIN_FILE=$EMSCRIPTEN/cmake/Modules/Platform/Emscripten.cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCMAKE_MODULE_PATH=$EMSCRIPTEN/Modules/cmake ../
make $*
