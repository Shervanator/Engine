#!/bin/bash

set -e

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

cmake --version
echo $ANDROID_NDK
ANDROID_NDK=$ANDROID_NDK $DIR/cmake-android.sh -j4
$DIR/cmake-make.sh -j4
