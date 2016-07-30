#!/bin/bash

set -e

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

$DIR/cmake-make.sh -j4
ANDROID_NDK=$ANDROID_NDK $DIR/cmake-android.sh -j4
