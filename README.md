# Engine

A basic cross-platform 3D game engine making use of:

- SDL2 window library.
- SOIL texture library (modified version for OpenGL 3).
- OpenGL 3.
- Assimp asset importing library.
- GLEW extension loading library.

## Usage

main.cpp

```c++
#include "Engine.h"

class CoolGame : public Game
{
public:
  CoolGame() {};

  virtual void init(void);

private:
  SceneNode *test_scene;
};

void CoolGame::init(void)
{
  test_scene = new SceneNode();
  test_scene->addObject(new VisibleObject(new Mesh("res/monkey3.obj"), new Texture("res/t.jpg")));
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
