#include "Engine.h"

#include "MeshRenderer.h"
#include "Mesh.h"
#include "Texture.h"
#include "Camera.h"
#include "FreeMove.h"
#include "FreeLook.h"
#include "DebugComponent.h"
#include "DirectionalLight.h"
#include "SpotLight.h"
#include "PointLight.h"
#include "Plane.h"
#include "Logger.h"
#include "MeshLoader.h"

#include "Sphere.h"

class CoolGame : public Game
{
public:
  virtual void init(GLManager *glManager);
  virtual void update(int delta);

private:
  Camera *primary_camera;
};

void CoolGame::update(int delta)
{
  static float angle = 0;
  angle += delta * 0.0008;
  // sun->getTransform().setPosition(glm::vec3(glm::sin(angle) * 5, 0, 0));

  Game::update(delta);
}

void CoolGame::init(GLManager *glManager)
{
  Entity *plane = new Entity();
  plane->addComponent(new MeshRenderer((new Plane())->getMesh(), new Material(new Texture(Asset("bricks2.jpg")), new Texture(Asset("bricks2_normal.jpg")), new Texture(Asset("bricks2_specular.png")))));
  plane->getTransform().setPosition(glm::vec3(0, -2, 0));
  plane->getTransform().setScale(glm::vec3(10, 10, 10));

  addToScene(plane);

  MeshLoader ml("Pregnant.obj");
  ml.getEntity()->getTransform().setPosition(glm::vec3(0, -2, 0));
  ml.getEntity()->addComponent(new Sphere(1));
  addToScene(ml.getEntity());

  MeshLoader money("monkey3.obj");
  money.getEntity()->getTransform().setPosition(glm::vec3(0, 0, 8));
  Camera *cam1 = new Camera(45.0f, getEngine()->getWindow()->getWidth() / (float)getEngine()->getWindow()->getHeight(), 0.9f, 100.0f);
  money.getEntity()->addComponent(cam1);
  money.getEntity()->addComponent(new Sphere(1));
  addToScene(money.getEntity());

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
  camera2Node->getTransform().setPosition(glm::vec3(0, 0, 0));
  camera2Node->getTransform().setScale(glm::vec3(0.8, 0.8, 0.8));
  camera2Node->addComponent(new PointLight(glm::vec3(1.0f, 1.0f, 1.0f), 0.6f, new Attenuation(0, 0, 0.05)));

  Entity *moneySmall = new Entity();
  moneySmall->addComponent(new MeshRenderer(new Mesh(Asset("monkey3.obj")), new Material(new Texture(Asset("t.jpg")))));
  moneySmall->getTransform().setPosition(glm::vec3(0, 2, 0));
  moneySmall->getTransform().setScale(glm::vec3(0.3, 0.3, 0.3));

  camera2Node->addChild(moneySmall);

  addToScene(camera2Node);

  primary_camera = cam2;
  
  getEngine()->getGLManager()->setActiveCamera(primary_camera);
}

int main(int argc, char **argv){
  CoolGame game;
  Engine gameEngine(&game);

  gameEngine.start();

  return 0;
}
