//
//  Author: Shervin Aflatooni
//

#include "Engine.h"

#include "components/MeshRenderer.h"
#include "components/PerspectiveCamera.h"
#include "components/OrthoCamera.h"
#include "components/FreeMove.h"
#include "components/FreeLook.h"
#include "components/DirectionalLight.h"
#include "components/SpotLight.h"
#include "components/PointLight.h"
#include "components/Sphere.h"

#include "Plane.h"
#include "Mesh.h"
#include "Texture.h"
#include "Logger.h"
#include "MeshLoader.h"

#include <SDL_main.h>

Entity *plane;

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
  // plane->getTransform().setRotation(glm::vec3(1, 0, 0), angle);
  //plane->getTransform().setPosition(glm::vec3(glm::sin(angle) * 5, 0, 0));

  Game::update(delta);
}

void CoolGame::init(GLManager *glManager)
{
  plane = new Entity();
  plane->addComponent<MeshRenderer>(new MeshRenderer((new Plane())->getMesh(), new Material(new Texture(Asset("bricks2.jpg")), new Texture(Asset("bricks2_normal.jpg")), new Texture(Asset("bricks2_specular.png")))));
  plane->getTransform().setPosition(glm::vec3(0, -2, 0));
  plane->getTransform().setScale(glm::vec3(10, 10, 10));

  addToScene(plane);

  for (int i = 0; i < 1; i++) {
    MeshLoader ml("Pregnant.obj");
    ml.getEntity()->getTransform().setPosition(glm::vec3(0 + (i * 3), -2, 0));
    ml.getEntity()->addComponent<Sphere>(new Sphere(1));
    addToScene(ml.getEntity());
  }

  MeshLoader money("monkey3.obj");
  money.getEntity()->getTransform().setPosition(glm::vec3(0, 0, 8));
  PerspectiveCamera *cam1 = new PerspectiveCamera(glm::pi<float>() / 2.0f, getEngine()->getWindow()->getWidth() / (float)getEngine()->getWindow()->getHeight(), 0.9f, 100.0f);
  money.getEntity()->addComponent<PerspectiveCamera>(cam1);
  money.getEntity()->addComponent<Sphere>(new Sphere(1));
  addToScene(money.getEntity());

  MeshLoader money2("monkey3.obj");
  PerspectiveCamera *cam2 = new PerspectiveCamera(glm::pi<float>() / 2.0f, getEngine()->getWindow()->getWidth() / (float)getEngine()->getWindow()->getHeight(), 0.9f, 100.0f);
  money2.getEntity()->addComponent<PerspectiveCamera>(cam2);
  money2.getEntity()->addComponent<FreeMove>(new FreeMove());
#if defined(ANDROID)
  money2.getEntity()->addComponent<FreeLook>(new FreeLook(0.0001f));
#else
  money2.getEntity()->addComponent<FreeLook>(new FreeLook());
#endif
  money2.getEntity()->getTransform().setPosition(glm::vec3(0, 0, 5));
  money2.getEntity()->getTransform().setScale(glm::vec3(0.8, 0.8, 0.8));
  money2.getEntity()->addComponent<SpotLight>(new SpotLight(glm::vec3(1.0f, 1.0f, 1.0f), 1.8f, 0.7f, new Attenuation(0, 0, 0.2)));

  addToScene(money2.getEntity());

  primary_camera = cam2;

  getEngine()->getGLManager()->setActiveCamera(primary_camera);
}

int main(int argc, char *argv[]) {
  CoolGame game;
  Engine gameEngine(&game);

  gameEngine.start();

  return 0;
}
