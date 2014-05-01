#include "Engine.h"

#include "VisibleObject.h"
#include "Mesh.h"
#include "Texture.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;

class CoolGame : public Game
{
public:
  virtual void init(void);
  virtual void update(int delta);

private:
  SceneNode *test_scene;
};

void CoolGame::update(int delta)
{
  static float rr = 0;
  rr += delta * 0.005;
  test_scene->getTransform().setPosition(glm::vec3(glm::sin(rr), 0, 0));
  test_scene->getTransform().setRotation(glm::vec3(1, 0, 0), glm::sin(rr));
}

void CoolGame::init(void)
{
  test_scene = new SceneNode();

  test_scene->getTransform().setPosition(glm::vec3(3, 0, 0));
  test_scene->getTransform().setRotation(glm::vec3(1, 0, 0), 45);

  SceneNode *testNode = new SceneNode();
  testNode->getTransform().setScale(glm::vec3(0.6, 1, 1));
  test_scene->addChild(testNode);

  GameObject *monkeyObject = new VisibleObject(new Mesh("res/monkey3.obj"), new Texture("res/t.jpg"));

  monkeyObject->getTransform().setScale(glm::vec3(0.3, 0.3, 0.3));
  monkeyObject->getTransform().setPosition(glm::vec3(1, 0, 0));

  testNode->addObject(monkeyObject);

  GameObject *monkeyObject2 = new VisibleObject(new Mesh("res/monkey3.obj"), new Texture("res/t.jpg"));

  monkeyObject2->getTransform().setScale(glm::vec3(0.5, 0.5, 0.5));
  monkeyObject2->getTransform().setPosition(glm::vec3(-1, 0, 0));
  monkeyObject2->getTransform().setRotation(glm::vec3(1, 0, 0), -45);

  test_scene->addObject(monkeyObject2);

  addToScene(test_scene);
}

int main(int argc, char **argv){
  CoolGame game;
  Engine gm(SCREEN_WIDTH, SCREEN_HEIGHT, &game);

  gm.start();

  return 0;
}
