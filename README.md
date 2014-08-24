# Engine

A basic cross-platform (Mac, Windows, HTML5) 3D game engine making use of:

- SDL2 window library.
- stb_image.h image library.
- OpenGL 3 / OpenGL ES 2.0.
- Assimp asset importing library.
- GLEW extension loading library.

## Usage

### To Build:

First install required libraries:

#### Mac Build
```
brew install sdl2
brew install assimp
brew install glew
```

After create the make file or project with cmake:

```
./cmake-make.sh
```

Then if in Mac or Linux:
```
cd bin
make
```

#### HTML 5 WebGL engine Build
To build the html5 engine use:

```
./cmake-emscripten.sh

# also need to compile assimp with emscripten:

git clone git@github.com:assimp/assimp.git
cd assimp
mkdir build.em
cd build.em
cmake -DEMSCRIPTEN=1 -DCMAKE_TOOLCHAIN_FILE=~/emsdk_portable/emscripten/1.21.0/cmake/Platform/Emscripten.cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_MODULE_PATH=~/emsdk_portable/emscripten/1.21.0/cmake  ..
make

# then build with:

cd bin-emscripten
make

python -m SimpleHTTPServer

open http://localhost:8000/game.html
```

#### Android Build

To build for android do the following:

First download the android ndk and sdk (https://developer.android.com/tools/sdk/ndk/) and (https://developer.android.com/sdk/index.html)
Then download the android ndk cmake toolchain (android.toolchain.cmake) from (https://code.google.com/p/android-cmake/)

```
export NDK_PATH=/path/to/your/android/ndk/

cd $NDK_PATH/build/tools

./make-standalone-toolchain.sh --platform=android-8 --install-dir=$HOME/android-toolchain --ndk-dir=$NDK_PATH –-toolchain=arm-linux-androideabi-4.4.3 --system=darwin-x86_64

export ANDROID_NDK_TOOLCHAIN=$HOME/android-toolchain

export ANDTOOLCHAIN=/path/to/android.toolchain.cmake

export PATH=$PATH:$HOME/path/to/android-sdk/tools

# compile assimp with android toolchain:

git clone git@github.com:assimp/assimp.git
cd assimp
mkdir build.android
cd build.android
cmake -DCMAKE_TOOLCHAIN_FILE=$ANDTOOLCHAIN -DCMAKE_INSTALL_PREFIX=/assimp-2.0 -DANDROID_ABI=armeabi-v7a _DANDROID_NATIVE_API_LEVEL=android-8 -DANDROID_FORCE_ARM_BUILD=TRUE ..

vim code/cMakeFiles/assimp.dir/link.txt
# search for the string "-soname, libassimp.so.3" and replace with "-soname, libassimp.so"

make

cd ../lib

# look for libassimp.so.some_version_number and rename it to libassimp.so

cp libassimp.so /path/to/engine/android/jni/src/libassimp.so

# Now add sdl src

cd /path/to/engine/android/jni/
# Download SDL source to this folder

# setup for android is now done!

cd /path/to/engine/android/

# build src for android with
ndk-build -j8

# create apk with
ant debug

# connect device and install apk with
adb install -r bin/SDLActivity-debug.apk

# view logs from device with
adb logcat | grep EngineLogger
```

### To Use:

To use the engine in a game build the engine library and include Engine.h in your game.

Eg:

```c++
#include "Engine.h"

class CoolGame : public Game
{
public:
  virtual void init(void);

private:
  SceneNode *test_scene;
};

void CoolGame::init(void)
{
  test_scene = new SceneNode();
  test_scene->addObject(new VisibleObject(new Mesh("../assets/monkey3.obj"), new Texture("../assets/t.jpg")));
  addToScene(test_scene);
}

int main(int argc, char **argv){
  CoolGame game;
  Engine gm(&game);

  gm.start();

  return 0;
}
```

## Contributing

1. Fork it ( http://github.com/Shervanator/Engine/fork )
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create new Pull Request
