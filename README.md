# Engine

A basic cross-platform (Mac, Windows, Linux, HTML5, Android) 3D game engine making use of:

- SDL2 window library.
- stb_image.h image library.
- OpenGL 3 / OpenGL ES 2.0 / OpenGL ES 3.0 Graphics APIs.
- Assimp asset importing library.
- GLEW extension loading library.

[![Build Status](https://travis-ci.org/Shervanator/Engine.svg?branch=master)](https://travis-ci.org/Shervanator/Engine)

## Usage

First clone repo with the following command to download all submodules (which are located in the dependencies folder):
`git clone --recursive git@github.com:Shervanator/Engine.git`

All builds require cmake 3.6.0, so the first step is to download that [here](https://cmake.org/download/)

#### Windows Build

1. Run the cmake gui and point it to this projects folder, configure and then generate a project using whatever toolchain you want. Tested with visual studio 2015
2. Build the project

#### Mac/Linux Build

Run:

```bash
./scripts/cmake-make.sh -j8
```

Then run with:
```bash
./bin/bin/game
```

This will run the first build for you! After that if you need to rebuild do the following:
```bash
cd bin
make -j8
```

#### HTML 5 WebGL engine Build

To build the html5 engine:

First install emscripten:
```bash
brew install emscripten
```

Then build the engine:
```bash
./scripts/cmake-emscripten.sh -j8
```

Then run with:
```bash
cd bin-emscripten/bin

python -m SimpleHTTPServer

open http://localhost:8000/
```

If you make a change you can rebuild with the following command:
```bash
cd bin-emscripten/
make -j8
```

#### Android Build

To build for android do the following:

First download the android ndk and sdk (https://developer.android.com/tools/sdk/ndk/) and (https://developer.android.com/sdk/index.html)

Then add the SDK and NDK to your path:

e.g. (you can add this to your .bash_profile for convenience)

```bash
export ANDROID_SDK=$HOME/Library/Android/sdk/
export ANDROID_NDK=$HOME/workspace/android-ndk-r12b

export PATH="$ANDROID_NDK:$ANDROID_SDK/tools:$ANDROID_SDK/platform-tools:$PATH"
```

Then to build (connect phone in dev mode to computer if you want it to install and run):
```
./scripts/cmake-android.sh -j8
```

To rebuild do the following:
```bash
cd bin-android
make -j8
make android-build android-install android-start
```

If you want to view the backtrace (to see logs and errors do the following):
```bash
cd bin-android
make android-backtrace
```

### To Use:

To use the engine in a game build the engine library and include Engine.h in your game.

View the example in `./src/example/main.cpp`

Or a simple case:

Eg:

```c++
#include "Engine.h"

class CoolGame : public Game
{
public:
  virtual void init(void);

private:
  Entity *test_entity;
};

void CoolGame::init(void)
{
  test_entity = new Entity();
  test_entity->addComponent(new MeshRenderer(new Mesh("../assets/monkey3.obj"), new Texture("../assets/t.jpg")));
  addToScene(test_entity);
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
