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
  SceneNode *moneyHead;
  SceneNode *moneySmall;
};

void CoolGame::update(int delta)
{
  static float rr = 0;
  rr += delta * 0.005;
  moneyHead->getTransform().setPosition(glm::vec3(glm::sin(rr), 0, 0));
  moneyHead->getTransform().setRotation(glm::vec3(1, 0, 0), glm::sin(rr));
}

void CoolGame::init(void)
{
  moneyHead = new SceneNode();
  moneyHead->addObject(new VisibleObject(new Mesh("res/monkey3.obj"), new Texture("res/t.jpg")));
  moneyHead->getTransform().setPosition(glm::vec3(3, 0, 0));

  moneySmall = new SceneNode();
  moneySmall->addObject(new VisibleObject(new Mesh("res/monkey3.obj"), new Texture("res/t.jpg")));
  moneySmall->getTransform().setPosition(glm::vec3(0, 1.5, 0));
  moneySmall->getTransform().setScale(glm::vec3(0.3, 0.3, 0.3));

  moneyHead->addChild(moneySmall);

  addToScene(moneyHead);
}

int main(int argc, char **argv){
  CoolGame game;
  Engine gm(SCREEN_WIDTH, SCREEN_HEIGHT, &game);

  gm.start();

  return 0;
}
