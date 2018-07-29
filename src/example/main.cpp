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
#include "components/BoxCollider.h"
#include "components/SphereCollider.h"

#include "Plane.h"
#include "Mesh.h"
#include "Texture.h"
#include "Logger.h"
#include "MeshLoader.h"

#include <SDL_main.h>
///////////////////////////////////////
///////////////////////////////////////
glm::vec3 groundVec[4] = {
    glm::vec3(-5, -2, 0),
    glm::vec3(5, -2, 0),
    glm::vec3(-5, -2, 10),
    glm::vec3(5, -2, 10),
}; // ground
    ///////////////////////////////////////
glm::vec3 wallVecs[8][2] = {
    glm::vec3(-5, 3, -5), glm::vec3(1, 0, 0), glm::vec3(5, 3, -5), glm::vec3(1, 0, 0),   // front wall
    glm::vec3(-5, 3, 15), glm::vec3(1, 0, 0), glm::vec3(5, 3, 15), glm::vec3(1, 0, 0),   // back wall
    glm::vec3(-10, 3, 0), glm::vec3(0, 0, 1), glm::vec3(-10, 3, 10), glm::vec3(0, 0, 1), // left wall
    glm::vec3(10, 3, 0), glm::vec3(0, 0, 1), glm::vec3(10, 3, 10), glm::vec3(0, 0, 1)};  // right wall
float wallRotates[4] = {glm::pi<float>() / 2.f, -glm::pi<float>() / 2.f, -glm::pi<float>() / 2.f, glm::pi<float>() / 2.f};
///////////////////////////////////////
///////////////////////////////////////
const std::string modelPath = "";

class CoolGame : public Game
{
  bool walking;
  SkeletalAnimationModelLoader *md5mesh, *astroBoy, *money, *skelete, *dancer, *testWuson;

public:
  CoolGame()
  {
    walking = false;
  } //*/
  virtual void init(GLManager *glManager);
  virtual void update(Input *input, std::chrono::microseconds delta);

  std::shared_ptr<PerspectiveCamera> primary_camera;
  std::shared_ptr<PerspectiveCamera> primary_camera2;
};

double timeElaped = 0.0;
void CoolGame::update(Input *input, std::chrono::microseconds delta)
{
  timeElaped += std::chrono::duration_cast<std::chrono::duration<float>>(delta).count();
  skelete->loadNewFrame(0, timeElaped);
  testWuson->loadNewFrame(0, timeElaped); //channel:0,1
  md5mesh->loadNewFrame(0, timeElaped);
  if (walking)
    astroBoy->loadNewFrame(0, timeElaped);
  else
    astroBoy->loadNewFrame(0, 0);

  Game::update(input, delta);
}

void CoolGame::init(GLManager *glManager)
{
  auto input = getEngine()->getWindow()->getInput();
  input->registerKeyToAction(SDLK_SPACE, "fire");
  input->registerKeyToAction(SDLK_c, "swapCamera");
  input->registerKeyToAction(SDLK_ESCAPE, "exit"); //Majid define this
  input->registerKeyToAction(SDLK_w, "Walking");   //Majid define this
  input->registerKeyToAction(SDLK_s, "Walking");   //Majid define this
  input->registerKeyToAction(SDLK_a, "Walking");   //Majid define this
  input->registerKeyToAction(SDLK_d, "Walking");   //Majid define this
  input->bindAction("Walking", IE_PRESSED, [this]() {
    walking = true;
  });
  input->bindAction("Walking", IE_RELEASED, [this]() {
    walking = false;
  });

  input->bindAction("fire", IE_PRESSED, [this]() {
    MeshLoader cube("cube.obj");
    cube.getEntity()->getTransform().setPosition(primary_camera->getParent()->getPosition()).setScale(glm::vec3(0.5, 0.5, 0.5));
    cube.getEntity()->addComponent<BoxCollider>(glm::vec3(0.5, 0.5, 0.5), 50);
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

  input->bindAction("exit", IE_PRESSED, [this]() {
    exit(0);
  });

  auto brickMat = std::make_shared<Material>(std::make_shared<Texture>(Asset("bricks2.jpg")), std::make_shared<Texture>(Asset("bricks2_normal.jpg")), std::make_shared<Texture>(Asset("bricks2_specular.png")));
  auto planeMesh = Plane::getMesh();

  for (int i = 0; i < 4; i++) // Draw ground
  {
    auto plane = std::make_shared<Entity>();
    plane->addComponent<MeshRenderer>(planeMesh, brickMat);
    plane->getTransform().setPosition(groundVec[i]).setScale(glm::vec3(10, 1, 10));
    plane->addComponent<BoxCollider>(glm::vec3(5, 0, 5), 0);
    addToScene(plane);
  } //*/

  for (int i = 0; i < 8; i++) // Draw walls
  {
    auto plane = std::make_shared<Entity>();
    plane->addComponent<MeshRenderer>(planeMesh, brickMat);
    plane->getTransform().setPosition(wallVecs[i][0]).setScale(glm::vec3(10, 1, 10)).rotate(wallVecs[i][1], wallRotates[(int)(i / 2)]);
    plane->addComponent<BoxCollider>(glm::vec3(5, 0, 5), 0);
    addToScene(plane);
  } //*/

  for (int i = 0; i < 2; i++)
  {
    MeshLoader ml("AncientUgandan.obj"); //"regr01.ply"
    ml.getEntity()->getTransform().setPosition(glm::vec3(0, i * 3, -2.5));
    ml.getEntity()->addComponent<SphereCollider>(1, 1);
    addToScene(ml.getEntity());
  }

  md5mesh = new SkeletalAnimationModelLoader("boblampclean.md5mesh");                                                              //:md5mesh("boblampclean.md5mesh"), skelete("01_03.bvh"),astroBoy("astroBoy_walk_Maya.dae"), testWuson("Testwuson.X")//, dogHouse("house.obj"), bigHouse("regr01.obj")
  skelete = new SkeletalAnimationModelLoader("Testwuson.X");                                                                       // , &glm::angleAxis(-glm::pi<float>() / 2.0f, glm::vec3(1.0f, 0.0f, 0.0f)), 0.05f); //:md5mesh("boblampclean.md5mesh"), skelete("01_03.bvh"),astroBoy("astroBoy_walk_Maya.dae"), testWuson("Testwuson.X")//, dogHouse("house.obj"), bigHouse("regr01.obj")
  astroBoy = new SkeletalAnimationModelLoader("Testwuson.X", glm::angleAxis(glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)), 0.1f); //astroBoy("astroBoy_walk_Maya.dae"), testWuson("Testwuson.X")//, dogHouse("house.obj"), bigHouse("regr01.obj")
  testWuson = new SkeletalAnimationModelLoader("Testwuson.X");                                                                     // testWuson("Testwuson.X")//, dogHouse("house.obj"), bigHouse("regr01.obj")
  MeshLoader money2("monkey3.obj");
  MeshLoader money3("monkey3.obj");

  md5mesh->getEntity()->getTransform().setPosition(glm::vec3(3, 1, -2)).setScale(glm::vec3(.05, .05, .05)).rotate(glm::vec3(1, 0, 0), glm::pi<float>() / 2.f);
  md5mesh->getEntity()->addComponent<SphereCollider>(1, 1);
  addToScene(md5mesh->getEntity());

  //skelete = new SkeletalAnimationModelLoader("Only_Spider_with_Animations_Export.dae", &glm::angleAxis(-glm::pi<float>() / 2.0f, glm::vec3(1.0f, 0.0f, 0.0f)), 0.02f); //:md5mesh("boblampclean.md5mesh"), skelete("01_03.bvh"),astroBoy("astroBoy_walk_Maya.dae"), testWuson("Testwuson.X")//, dogHouse("house.obj"), bigHouse("regr01.obj")
  //skelete = new SkeletalAnimationModelLoader("Dragon2.5_dae.dae", &glm::angleAxis(-glm::pi<float>() / 2.0f, glm::vec3(1.0f, 0.0f, 0.0f)), 0.05f); //:md5mesh("boblampclean.md5mesh"), skelete("01_03.bvh"),astroBoy("astroBoy_walk_Maya.dae"), testWuson("Testwuson.X")//, dogHouse("house.obj"), bigHouse("regr01.obj")
  //skelete = new SkeletalAnimationModelLoader("T-Rex.fbx");// , &glm::angleAxis(-glm::pi<float>() / 2.0f, glm::vec3(1.0f, 0.0f, 0.0f)), 0.001f); //:md5mesh("boblampclean.md5mesh"), skelete("01_03.bvh"),astroBoy("astroBoy_walk_Maya.dae"), testWuson("Testwuson.X")//, dogHouse("house.obj"), bigHouse("regr01.obj")
  //skelete = new SkeletalAnimationModelLoader("Wolf_One_dae.dae");// , &glm::angleAxis(-glm::pi<float>() / 2.0f, glm::vec3(1.0f, 0.0f, 0.0f)), 0.001f); //:md5mesh("boblampclean.md5mesh"), skelete("01_03.bvh"),astroBoy("astroBoy_walk_Maya.dae"), testWuson("Testwuson.X")//, dogHouse("house.obj"), bigHouse("regr01.obj")
  skelete->getEntity()->getTransform().setPosition(glm::vec3(6, 1, -3)); //.setScale(glm::vec3(0.05, 0.05, 0.05));
  skelete->getEntity()->addComponent<SphereCollider>(1, 1);
  addToScene(skelete->getEntity());

  astroBoy->getEntity()->getTransform().setPosition(glm::vec3(3, 0, 2)); // .setScale(glm::vec3(.1, .1, .1));// .rotate(glm::vec3(0, 1, 0), glm::pi<float>());
  astroBoy->getEntity()->addComponent<PerspectiveCamera>(glm::pi<float>() / 2.0f, getEngine()->getWindow()->getWidth() / (float)getEngine()->getWindow()->getHeight(), 0.8f, 100.0f);
  astroBoy->getEntity()->getComponent<PerspectiveCamera>()->getTransform().setPosition(glm::vec3(0.0f, 2.5f, 3.0f)); // .rotate(glm::vec3(1, 0, 0), glm::pi<float>());
  astroBoy->getEntity()->addComponent<FreeMove>();
#if defined(ANDROID)
  astroBoy->getEntity()->addComponent<FreeLook>(0.1f);
#else
  astroBoy->getEntity()->addComponent<FreeLook>();
#endif
  astroBoy->getEntity()->addComponent<SpotLight>(glm::vec3(1.0f, 1.0f, 1.0f), 2.8f, 0.7f, std::make_shared<Attenuation>(0, 0, 0.2)); //*/
  //astroBoy->getEntity()->addComponent<SphereCollider>(1, 1);
  addToScene(astroBoy->getEntity());

  testWuson->getEntity()->getTransform().setPosition(glm::vec3(-3, 0, 0));
  testWuson->getEntity()->addComponent<SphereCollider>(1, 1);
  addToScene(testWuson->getEntity()); //*/

  money2.getEntity()->getTransform().setPosition(glm::vec3(0, 0, 5)).setScale(glm::vec3(0.8, 0.8, 0.8));
  money2.getEntity()->addComponent<SphereCollider>(1, 1);
  addToScene(money2.getEntity());

  money3.getEntity()->getTransform().setPosition(glm::vec3(0, 0, 10));
  ///////////////////////////////////////////////////PerspectiveCamera(float fov, float aspect, float zNear, float zFar)
  money3.getEntity()->addComponent<PerspectiveCamera>(glm::pi<float>() / 2.0f, getEngine()->getWindow()->getWidth() / (float)getEngine()->getWindow()->getHeight(), 0.05f, 100.0f);
  //money3.getEntity()->addComponent<FreeMove>();
  money3.getEntity()->addComponent<SphereCollider>(1, 1);
  addToScene(money3.getEntity());

  primary_camera = astroBoy->getEntity()->getComponent<PerspectiveCamera>();
  primary_camera2 = money3.getEntity()->getComponent<PerspectiveCamera>();

  getEngine()->getGLManager()->setActiveCamera(primary_camera);
}

int main(int argc, char *argv[])
{
  CoolGame game;
  Engine gameEngine(&game);

  gameEngine.start();
  return 0;
}
