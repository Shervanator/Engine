#include "Engine.h"

#include "VisibleObject.h"
#include "Mesh.h"
#include "Texture.h"
#include "Camera.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;

class CoolGame : public Game
{
public:
  virtual void init(void);
  virtual void render(GLManager *glManager);
  virtual void update(int delta, KeyboardHandler *keyboardHandler);

private:
  SceneNode *moneyHead;
  SceneNode *moneySmall;

  SceneNode *cameraNode;
  Camera *primary_camera;
};

void CoolGame::render(GLManager *glManager)
{
  glManager->setViewProjection(primary_camera->getViewProjection());

  Game::render(glManager);
}

void CoolGame::update(int delta, KeyboardHandler *keyboardHandler)
{
  static float rr = 0;
  rr += delta * 0.005;
  moneyHead->getTransform().setPosition(glm::vec3(glm::sin(rr), 0, 0));
  moneyHead->getTransform().setRotation(glm::vec3(1, 0, 0), glm::sin(rr));

  if (keyboardHandler->isPressed(SDLK_UP)) {
    primary_camera->moveY(1.0f);
  }

  if (keyboardHandler->isPressed(SDLK_DOWN)) {
    primary_camera->moveY(-1.0f);
  }

  if (keyboardHandler->isPressed(SDLK_LEFT)) {
    primary_camera->moveX(-1.0f);
  }

  if (keyboardHandler->isPressed(SDLK_RIGHT)) {
    primary_camera->moveX(1.0f);
  }

  if (keyboardHandler->isReleased(SDLK_UP) && keyboardHandler->isReleased(SDLK_DOWN)) {
    primary_camera->moveY(0.0f);
  }

  if (keyboardHandler->isReleased(SDLK_LEFT) && keyboardHandler->isReleased(SDLK_RIGHT)) {
    primary_camera->moveX(0.0f);
  }
  
  Game::update(delta, keyboardHandler);
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

  cameraNode = new SceneNode();

  primary_camera = new Camera(glm::vec3(0, 0, 10), 45.0f, SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
  cameraNode->addObject(primary_camera);

  addToScene(cameraNode);
}

int main(int argc, char **argv){
  CoolGame game;
  Engine gm(SCREEN_WIDTH, SCREEN_HEIGHT, &game);

  gm.start();

  return 0;
}
