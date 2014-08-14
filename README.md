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
mkdir bin
cd bin
cmake ../src/
```

Then if in Mac or Linux:
```
make
```

If in Windows open the visual studio solution file.

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
