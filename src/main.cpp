//
//  Author: Shervin Aflatooni
//

#include "Engine.h"

#include "components/MeshRenderer.h"
#include "components/Camera.h"
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
#include "SceneLoader.h"
#include "Video.h"
// #include "AnimationLoader.h"

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
  // AnimationLoader al("RotatingCircularLogoDark.dae");

  // MeshLoader ml("RotatingCircularLogoDark.dae");
  // ml.getEntity()->getTransform().setPosition(glm::vec3(0, -2, 0));
  // ml.getEntity()->addComponent(new Sphere(1));
  // addToScene(ml.getEntity());

  SceneLoader sl("RotatingCircularLogoDark.dae");
  // sl.getEntity()->addComponent(new FreeMove());
  // sl.getEntity()->addComponent(new FreeLook());
  addToScene(sl.getEntity());
  primary_camera = sl.getCamera();

  // money2.getEntity()->addComponent(new FreeMove());
  // money2.getEntity()->addComponent(new FreeLook());
  //
  // MeshLoader money2("monkey3.obj");
  // // Entity *money2 = new Entity();
  // Camera *cam2 = new Camera(45.0f, getEngine()->getWindow()->getWidth() / (float)getEngine()->getWindow()->getHeight(), 0.1f, 100.0f);
  // money2.getEntity()->addComponent(cam2);
  // money2.getEntity()->addComponent(new FreeMove());
  // money2.getEntity()->addComponent(new FreeLook());
  // money2.getEntity()->getTransform().setPosition(glm::vec3(0, 0, 5));
  // money2.getEntity()->getTransform().setScale(glm::vec3(0.8, 0.8, 0.8));
  // money2.getEntity()->addComponent(new PointLight(glm::vec3(1.0f, 1.0f, 1.0f), 0.6f, new Attenuation(0, 0, 0.05)));
  //
  // addToScene(money2.getEntity());

  // primary_camera = cam2;

  Entity *lensFlare = new Entity();
  // lensFlare->getTransform().setRotation(primary_camera->getParent()->getTransform().getRotation());
  Video *video = new Video("../assets/Flares.mp4");
  TextureData *textureData = new TextureData(video->getWidth(), video->getHeight(), video->nextFrame(), GL_RGB, GL_TEXTURE_2D, GL_LINEAR);
  Texture *texture = new Texture(textureData);
  lensFlare->addComponent(new MeshRenderer((new Plane())->getMesh(), new Material(texture)));
  float aR = texture->getTextureData()->getWidth() / (texture->getTextureData()->getHeight() * 1.0f);
  lensFlare->getTransform().setScale(glm::vec3(aR, 1, 1));
  textureData->updateTexture(video->nextFrame());
  
  addToScene(lensFlare);

  Entity *light = new Entity();
  light->addComponent(new DirectionalLight(glm::vec3(1.0f, 1.0f, 1.0f), 1.0f));

  addToScene(light);

  getEngine()->getGLManager()->setActiveCamera(primary_camera);
}

int main(int argc, char **argv){
  CoolGame game;
  Engine gameEngine(&game);

  gameEngine.start();

  return 0;
}
