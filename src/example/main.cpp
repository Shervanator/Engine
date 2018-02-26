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
#include "components/BoxCollider.h"
#include "components/SphereCollider.h"

#include "Plane.h"
#include "Mesh.h"
#include "Texture.h"
#include "Logger.h"
#include "MeshLoader.h"

#include <SDL_main.h>

class CoolGame : public Game
{
public:
  virtual void init(GLManager *glManager);
  virtual void update(Input *input, std::chrono::microseconds delta);

  std::shared_ptr<PerspectiveCamera> primary_camera;
  std::shared_ptr<PerspectiveCamera> primary_camera2;
};

void CoolGame::update(Input *input, std::chrono::microseconds delta)
{
  Game::update(input, delta);
}

void CoolGame::init(GLManager *glManager)
{
  auto input = getEngine()->getWindow()->getInput();
  input->registerKeyToAction(SDLK_SPACE, "fire");
  input->registerKeyToAction(SDLK_c, "swapCamera");

  input->bindAction("fire", IE_PRESSED, [this]() {
    MeshLoader cube("cube.obj");
    cube.getEntity()->getTransform().setPosition(primary_camera->getParent()->getPosition());
    cube.getEntity()->addComponent<BoxCollider>(glm::vec3(0.5, 0.5, 0.5), 50);
    cube.getEntity()->addComponent<Sphere>(1);
    addToScene(cube.getEntity());
    auto dir = primary_camera->getParent()->getDirection();
    cube.getEntity()->getComponent<BoxCollider>()->applyCentralImpulse(glm::vec3(dir.x * 500.0f, dir.y * 500.0f, dir.z * 500.0f));
  });

  input->bindAction("swapCamera", IE_PRESSED, [this]() {
    getEngine()->getGLManager()->setActiveCamera(primary_camera2);
  });

  input->bindAction("swapCamera", IE_RELEASED, [this]() {
    getEngine()->getGLManager()->setActiveCamera(primary_camera);
  });

  auto brickMat = std::make_shared<Material>(std::make_shared<Texture>(Asset("bricks2.jpg")), std::make_shared<Texture>(Asset("bricks2_normal.jpg")), std::make_shared<Texture>(Asset("bricks2_specular.png")));
  auto planeMesh = Plane::getMesh();
  // ground
  {
    auto plane = std::make_shared<Entity>();
    plane->addComponent<MeshRenderer>(planeMesh, brickMat);
    plane->getTransform().setPosition(glm::vec3(-5, -2, 0)).setScale(glm::vec3(10, 1, 10));
    plane->addComponent<BoxCollider>(glm::vec3(5, 0, 5), 0);

    addToScene(plane);
  }
  {
    auto plane = std::make_shared<Entity>();
    plane->addComponent<MeshRenderer>(planeMesh, brickMat);
    plane->getTransform().setPosition(glm::vec3(5, -2, 0)).setScale(glm::vec3(10, 1, 10));
    plane->addComponent<BoxCollider>(glm::vec3(5, 0, 5), 0);

    addToScene(plane);
  }
  {
    auto plane = std::make_shared<Entity>();
    plane->addComponent<MeshRenderer>(planeMesh, brickMat);
    plane->getTransform().setPosition(glm::vec3(-5, -2, 10)).setScale(glm::vec3(10, 1, 10));
    plane->addComponent<BoxCollider>(glm::vec3(5, 0, 5), 0);

    addToScene(plane);
  }
  {
    auto plane = std::make_shared<Entity>();
    plane->addComponent<MeshRenderer>(planeMesh, brickMat);
    plane->getTransform().setPosition(glm::vec3(5, -2, 10)).setScale(glm::vec3(10, 1, 10));
    plane->addComponent<BoxCollider>(glm::vec3(5, 0, 5), 0);

    addToScene(plane);
  }

  // front wall
  {
    auto plane = std::make_shared<Entity>();
    plane->addComponent<MeshRenderer>(planeMesh, brickMat);
    plane->getTransform()
        .setPosition(glm::vec3(-5, 3, -5))
        .setScale(glm::vec3(10, 1, 10))
        .rotate(glm::vec3(1, 0, 0), glm::pi<float>() / 2.f);
    plane->addComponent<BoxCollider>(glm::vec3(5, 0, 5), 0);

    addToScene(plane);
  }
  {
    auto plane = std::make_shared<Entity>();
    plane->addComponent<MeshRenderer>(planeMesh, brickMat);
    plane->getTransform()
        .setPosition(glm::vec3(5, 3, -5))
        .setScale(glm::vec3(10, 1, 10))
        .rotate(glm::vec3(1, 0, 0), glm::pi<float>() / 2.f);
    plane->addComponent<BoxCollider>(glm::vec3(5, 0, 5), 0);

    addToScene(plane);
  }

  // back wall
  {
    auto plane = std::make_shared<Entity>();
    plane->addComponent<MeshRenderer>(planeMesh, brickMat);
    plane->getTransform()
        .setPosition(glm::vec3(-5, 3, 15))
        .setScale(glm::vec3(10, 1, 10))
        .rotate(glm::vec3(1, 0, 0), -glm::pi<float>() / 2.f);
    plane->addComponent<BoxCollider>(glm::vec3(5, 0, 5), 0);

    addToScene(plane);
  }
  {
    auto plane = std::make_shared<Entity>();
    plane->addComponent<MeshRenderer>(planeMesh, brickMat);
    plane->getTransform()
        .setPosition(glm::vec3(5, 3, 15))
        .setScale(glm::vec3(10, 1, 10))
        .rotate(glm::vec3(1, 0, 0), -glm::pi<float>() / 2.f);
    plane->addComponent<BoxCollider>(glm::vec3(5, 0, 5), 0);

    addToScene(plane);
  }

  // left wall
  {
    auto plane = std::make_shared<Entity>();
    plane->addComponent<MeshRenderer>(planeMesh, brickMat);
    plane->getTransform()
        .setPosition(glm::vec3(-10, 3, 0))
        .setScale(glm::vec3(10, 1, 10))
        .rotate(glm::vec3(0, 0, 1), -glm::pi<float>() / 2.f);
    plane->addComponent<BoxCollider>(glm::vec3(5, 0, 5), 0);

    addToScene(plane);
  }
  {
    auto plane = std::make_shared<Entity>();
    plane->addComponent<MeshRenderer>(planeMesh, brickMat);
    plane->getTransform()
        .setPosition(glm::vec3(-10, 3, 10))
        .setScale(glm::vec3(10, 1, 10))
        .rotate(glm::vec3(0, 0, 1), -glm::pi<float>() / 2.f);
    plane->addComponent<BoxCollider>(glm::vec3(5, 0, 5), 0);

    addToScene(plane);
  }

  // right wall
  {
    auto plane = std::make_shared<Entity>();
    plane->addComponent<MeshRenderer>(planeMesh, brickMat);
    plane->getTransform()
        .setPosition(glm::vec3(10, 3, 0))
        .setScale(glm::vec3(10, 1, 10))
        .rotate(glm::vec3(0, 0, 1), glm::pi<float>() / 2.f);
    plane->addComponent<BoxCollider>(glm::vec3(5, 0, 5), 0);

    addToScene(plane);
  }
  {
    auto plane = std::make_shared<Entity>();
    plane->addComponent<MeshRenderer>(planeMesh, brickMat);
    plane->getTransform()
        .setPosition(glm::vec3(10, 3, 10))
        .setScale(glm::vec3(10, 1, 10))
        .rotate(glm::vec3(0, 0, 1), glm::pi<float>() / 2.f);
    plane->addComponent<BoxCollider>(glm::vec3(5, 0, 5), 0);

    addToScene(plane);
  }

  for (int i = 0; i < 1; i++)
  {
    MeshLoader ml("Pregnant.obj");
    ml.getEntity()->getTransform().setPosition(glm::vec3(0 + (i * 3), -2, -2.5));
    ml.getEntity()->addComponent<Sphere>(1);
    addToScene(ml.getEntity());
  }

  {
    MeshLoader ml("AncientUgandan.obj");
    ml.getEntity()->getTransform().setPosition(glm::vec3(0, 0, -2.5));
    ml.getEntity()->addComponent<Sphere>(1);
    ml.getEntity()->addComponent<SphereCollider>(1, 1);
    addToScene(ml.getEntity());
  }

  MeshLoader money("monkey3.obj");
  money.getEntity()->getTransform().setPosition(glm::vec3(0, 0, 8));
  money.getEntity()->addComponent<PerspectiveCamera>(glm::pi<float>() / 2.0f, getEngine()->getWindow()->getWidth() / (float)getEngine()->getWindow()->getHeight(), 0.05f, 100.0f);
  money.getEntity()->addComponent<Sphere>(1);
  money.getEntity()->addComponent<SpotLight>(glm::vec3(0.1f, 1.0f, 1.0f), 5.8f, 0.7f, std::make_shared<Attenuation>(0, 0, 0.2));
  money.getEntity()->addComponent<SphereCollider>(1, 1);
  addToScene(money.getEntity());

  MeshLoader money2("monkey3.obj");
  money2.getEntity()->addComponent<PerspectiveCamera>(glm::pi<float>() / 2.0f, getEngine()->getWindow()->getWidth() / (float)getEngine()->getWindow()->getHeight(), 0.8f, 100.0f);
  money2.getEntity()->addComponent<FreeMove>();
#if defined(ANDROID)
  money2.getEntity()->addComponent<FreeLook>(0.1f);
#else
  money2.getEntity()->addComponent<FreeLook>();
#endif
  money2.getEntity()->getTransform().setPosition(glm::vec3(0, 0, 5)).setScale(glm::vec3(0.8, 0.8, 0.8));
  money2.getEntity()->addComponent<SpotLight>(glm::vec3(1.0f, 1.0f, 1.0f), 2.8f, 0.7f, std::make_shared<Attenuation>(0, 0, 0.2));

  addToScene(money2.getEntity());

  primary_camera = money2.getEntity()->getComponent<PerspectiveCamera>();
  primary_camera2 = money.getEntity()->getComponent<PerspectiveCamera>();

  getEngine()->getGLManager()->setActiveCamera(primary_camera);
}

int main(int argc, char *argv[])
{
  CoolGame game;
  Engine gameEngine(&game);

  gameEngine.start();

  return 0;
}
