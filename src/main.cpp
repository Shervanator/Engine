#include "Engine.h"

#include "MeshRenderer.h"
#include "Mesh.h"
#include "Texture.h"
#include "Camera.h"
#include "FreeMove.h"
#include "FreeLook.h"
#include "DebugComponent.h"

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
  glManager->setViewProjection(primary_camera->getViewProjection());

  Game::render(glManager);
}

void CoolGame::updateInput(Input *input, int delta)
{
  static float rr = 0;
  rr += delta * 0.005;
  // moneyHead->getTransform().setPosition(glm::vec3(0, 0, glm::sin(rr)));
  //moneyHead->getTransform().setRotation(glm::vec3(1, 0, 0), glm::sin(rr));

  // if (input->isPressed(SDLK_UP)) {
  //   primary_camera->moveY(1.0f);
  // }

  Game::updateInput(input, delta);
}

void CoolGame::init(void)
{
  moneyHead = new Entity();
  moneyHead->addComponent(new MeshRenderer(new Mesh(Asset("monkey3.obj")), new Texture(Asset("t.jpg"))));
  moneyHead->getTransform().setPosition(glm::vec3(0, 0, 0));
  moneyHead->getTransform().setScale(glm::vec3(2.3, 2.3, 2.3));
  moneyHead->getTransform().rotate(glm::vec3(0, 1, 0), 3.1415);

  moneySmall = new Entity();
  moneySmall->addComponent(new MeshRenderer(new Mesh(Asset("monkey3.obj")), new Texture(Asset("t.jpg"))));
  moneySmall->getTransform().setPosition(glm::vec3(0, 1.5, 0));
  moneySmall->getTransform().setScale(glm::vec3(0.3, 0.3, 0.3));

  moneyHead->addChild(moneySmall);

  addToScene(moneyHead);

  cameraNode = new Entity();

  cameraNode->addComponent(new Camera(45.0f, getEngine()->getWindow()->getWidth() / (float)getEngine()->getWindow()->getHeight(), 0.1f, 100.0f));
  cameraNode->addComponent(new MeshRenderer(new Mesh(Asset("monkey3.obj")), new Texture(Asset("t.jpg"))));
  cameraNode->getTransform().setPosition(glm::vec3(0, 0, 20));

  addToScene(cameraNode);

  Entity *camera2Node = new Entity();

  primary_camera = new Camera(45.0f, getEngine()->getWindow()->getWidth() / (float)getEngine()->getWindow()->getHeight(), 1.1f, 100.0f);
  camera2Node->addComponent(primary_camera);
  camera2Node->addComponent(new FreeMove());
#if defined(ANDROID)
  camera2Node->addComponent(new FreeLook(0.0001f));
#else
  camera2Node->addComponent(new FreeLook());
#endif
  camera2Node->addComponent(new MeshRenderer(new Mesh(Asset("monkey3.obj")), new Texture(Asset("t.jpg"))));
  camera2Node->getTransform().setPosition(glm::vec3(0, 0, 5));

  addToScene(camera2Node);
}

int main(int argc, char **argv){
  CoolGame game;
  Engine gm(&game);

  gm.start();

  return 0;
}
