#include "Engine.h"

#include "MeshRenderer.h"
#include "Mesh.h"
#include "Texture.h"
#include "Camera.h"

class CoolGame : public Game
{
public:
  virtual void init(void);
  virtual void render(GLManager *glManager);
  virtual void updateInput(Input *input, int delta);

private:
  Entity *moneyHead;
  Entity *moneySmall;

  Entity *cameraNode;
  Camera *primary_camera;
};

void CoolGame::render(GLManager *glManager)
{
  primary_camera->setAspect(glManager->width/(float)glManager->height);
  glManager->setViewProjection(primary_camera->getViewProjection());

  Game::render(glManager);
}

void CoolGame::updateInput(Input *input, int delta)
{
  static float rr = 0;
  rr += delta * 0.005;
  moneyHead->getTransform().setPosition(glm::vec3(0, 0, glm::sin(rr)));
  //moneyHead->getTransform().setRotation(glm::vec3(1, 0, 0), glm::sin(rr));

  if (input->isPressed(SDLK_UP)) {
    primary_camera->moveY(1.0f);
  }

  if (input->isPressed(SDLK_DOWN)) {
    primary_camera->moveY(-1.0f);
  }

  if (input->isPressed(SDLK_LEFT)) {
    primary_camera->moveX(-1.0f);
  }

  if (input->isPressed(SDLK_RIGHT)) {
    primary_camera->moveX(1.0f);
  }

  if (input->isReleased(SDLK_UP) && input->isReleased(SDLK_DOWN)) {
    primary_camera->moveY(0.0f);
  }

  if (input->isReleased(SDLK_LEFT) && input->isReleased(SDLK_RIGHT)) {
    primary_camera->moveX(0.0f);
  }

  Game::updateInput(input, delta);
}

void CoolGame::init(void)
{
  moneyHead = new Entity();
  moneyHead->addComponent(new MeshRenderer(new Mesh(Asset("monkey3.obj")), new Texture(Asset("t.jpg"))));
  moneyHead->getTransform().setPosition(glm::vec3(5, 0, 0));
  moneyHead->getTransform().setScale(glm::vec3(4.3, 4.3, 4.3));

  moneySmall = new Entity();
  moneySmall->addComponent(new MeshRenderer(new Mesh(Asset("monkey3.obj")), new Texture(Asset("t.jpg"))));
  moneySmall->getTransform().setPosition(glm::vec3(0, 1.5, 0));
  moneySmall->getTransform().setScale(glm::vec3(0.3, 0.3, 0.3));

  moneyHead->addChild(moneySmall);

  addToScene(moneyHead);

  cameraNode = new Entity();

  primary_camera = new Camera(45.0f, 100 / (float)100, 0.1f, 100.0f);
  cameraNode->addComponent(primary_camera);
  cameraNode->getTransform().setPosition(glm::vec3(0, 0, 10));

  addToScene(cameraNode);
}

int main(int argc, char **argv){
  CoolGame game;
  Engine gm(&game);

  gm.start();

  return 0;
}
