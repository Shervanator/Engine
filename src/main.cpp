#include "Engine.h"

#include "VisibleObject.h"
#include "Mesh.h"
#include "Texture.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;

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
