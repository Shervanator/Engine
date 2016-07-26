#!/bin/bash

set -e

EMSCRIPTEN_PATH=${EMSCRIPTEN_PATH:-/usr/local/opt/emscripten/libexec}
BUILD_TYPE=${BUILD_TYPE:-Release}
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
mkdir -p $DIR/../bin-emscripten
mkdir -p $DIR/../bin-emscripten/bin/
cp $DIR/../src/html/index.html $DIR/../bin-emscripten/bin/
cd $DIR/../bin-emscripten
cmake -DEMSCRIPTEN=1 -DCMAKE_TOOLCHAIN_FILE=$EMSCRIPTEN_PATH/cmake/Modules/Platform/Emscripten.cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCMAKE_MODULE_PATH=$EMSCRIPTEN_PATH/Modules/cmake ../
make $*
