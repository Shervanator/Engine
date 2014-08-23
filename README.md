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

#### Mac:
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

If in Windows open the visual studio solution file.

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
```

then build with:
```
cd bin-emscripten
make

open game.html
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
  Engine gm(SCREEN_WIDTH, SCREEN_HEIGHT, &game);

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
