#include "Engine.h"

#include "MeshRenderer.h"
#include "Mesh.h"
#include "Texture.h"
#include "Camera.h"
#include "FreeMove.h"
#include "FreeLook.h"
#include "DebugComponent.h"
#include "DirectionalLight.h"
#include "Logger.h"

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
  DirectionalLight *dl;
};

void CoolGame::render(GLManager *glManager)
{
  glManager->setActiveCamera(primary_camera);
  glManager->setActiveLight(dl);

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
  moneyHead->addComponent(new MeshRenderer(new Mesh(Asset("Pregnant.obj")), new Material(new Texture(Asset("Pregnant_D.tga")))));
  moneyHead->getTransform().setPosition(glm::vec3(0, -2, 0));
  moneyHead->getTransform().setScale(glm::vec3(2.3, 2.3, 2.3));
  moneyHead->getTransform().setScale(glm::vec3(0.7, 0.7, 0.7));


  moneySmall = new Entity();
  moneySmall->addComponent(new MeshRenderer(new Mesh(Asset("monkey3.obj")), new Material(new Texture(Asset("t.jpg")))));
  moneySmall->getTransform().setPosition(glm::vec3(0, 1.5, 0));
  moneySmall->getTransform().setScale(glm::vec3(0.3, 0.3, 0.3));

  moneyHead->addChild(moneySmall);

  addToScene(moneyHead);

  cameraNode = new Entity();

  Camera *cam1 = new Camera(45.0f, getEngine()->getWindow()->getWidth() / (float)getEngine()->getWindow()->getHeight(), 0.9f, 100.0f);
  cameraNode->addComponent(cam1);
  cameraNode->addComponent(new MeshRenderer(new Mesh(Asset("monkey3.obj")), new Material(new Texture(Asset("t.jpg")))));
  cameraNode->getTransform().setPosition(glm::vec3(0, 0, 20));
  dl = new DirectionalLight(glm::vec3(1.0f, 1.0f, 1.0f), 0.5);
  cameraNode->addComponent(dl);

  addToScene(cameraNode);

  Entity *camera2Node = new Entity();

  Camera *cam2 = new Camera(45.0f, getEngine()->getWindow()->getWidth() / (float)getEngine()->getWindow()->getHeight(), 0.1f, 100.0f);
  camera2Node->addComponent(cam2);
  camera2Node->addComponent(new FreeMove());
#if defined(ANDROID)
  camera2Node->addComponent(new FreeLook(0.0001f));
#else
  camera2Node->addComponent(new FreeLook());
#endif
  camera2Node->addComponent(new MeshRenderer(new Mesh(Asset("monkey3.obj")), new Material(new Texture(Asset("t.jpg")))));
  camera2Node->getTransform().setPosition(glm::vec3(0, 0, 5));

  addToScene(camera2Node);

  primary_camera = cam2;
}

int main(int argc, char **argv){
  CoolGame game;
  Engine gm(&game);

  gm.start();

  return 0;
}
