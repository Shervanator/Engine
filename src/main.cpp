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
#include "components/VideoAnimation.h"

#include "Plane.h"
#include "Mesh.h"
#include "Texture.h"
#include "Logger.h"
#include "MeshLoader.h"
#include "SceneLoader.h"
#include "Video.h"

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
  SceneLoader sl("RotatingCircularLogoDark.dae");
  addToScene(sl.getEntity());
  primary_camera = sl.getCamera();

  Entity *lensFlareCameraEntity = new Entity();
  Camera *lensFlareCamera = new Camera(0, 1920.0f/1080.0f, 0, 0);
  lensFlareCameraEntity->addComponent(lensFlareCamera);

  Entity *lensFlare = new Entity();
  Video *video = new Video("../assets/Flares.mp4");
  TextureData *textureData = new TextureData(video->getWidth(), video->getHeight(), video->nextFrame(), GL_RGB, GL_TEXTURE_2D, GL_LINEAR);
  Texture *texture = new Texture(textureData);
  lensFlare->addComponent(new MeshRenderer((new Plane())->getMesh(), new Material(texture)));
  float aR = texture->getTextureData()->getWidth() / (texture->getTextureData()->getHeight() * 1.0f);
  lensFlare->getTransform().setScale(glm::vec3(aR, 1, 1));
  lensFlare->getTransform().scale(glm::vec3(100, 100, 100));
  lensFlare->getTransform().rotate(glm::vec3(1, 0, 0), glm::radians(90.0f));
  lensFlare->addComponent(new VideoAnimation(textureData, video));

  addToScene(lensFlareCameraEntity, 1);
  addToScene(lensFlare, 1);

  Entity *light = new Entity();
  light->addComponent(new DirectionalLight(glm::vec3(1.0f, 1.0f, 1.0f), 1.0f));

  addToScene(light);

  getEngine()->getGLManager()->setUICamera(lensFlareCamera);
  getEngine()->getGLManager()->setActiveCamera(primary_camera);
}

int main(int argc, char **argv){
  CoolGame game;
  Engine gameEngine(&game);

  gameEngine.start();

  return 0;
}
