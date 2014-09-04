#include "GLManager.h"

#include "FreeLook.h"
#include "FreeMove.h"

GLManager::GLManager(int width, int height)
{
  this->width = width;
  this->height = height;
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  glClearDepthf(1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glEnable(GL_CULL_FACE);

  glViewport(0, 0, this->width, this->height);

  createShaders();
}

GLManager::~GLManager(void)
{
  delete forwardAmbient;
  delete forwardDirectional;
}

void GLManager::setActiveCamera(Camera *camera)
{
  m_activeCamera = camera;
}

void GLManager::setActiveLight(DirectionalLight *light)
{
  m_activeLight = light;
}

void GLManager::renderScene(Entity *scene)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  forwardAmbient->setUniformMatrix4f("ViewProj", m_activeCamera->getViewProjection());

  scene->renderAll(forwardAmbient);

  glEnable(GL_BLEND);
  glBlendFunc(GL_ONE, GL_ONE);
  glDepthMask(GL_FALSE);
  glDepthFunc(GL_EQUAL);

  forwardDirectional->setUniformMatrix4f("ViewProj", m_activeCamera->getViewProjection());
  forwardDirectional->setUniformVec3f("eyePos", m_activeCamera->getTransform().getPosition());
  forwardDirectional->setUniform1f("specularIntensity", 1);
  forwardDirectional->setUniform1f("specularPower", 10);
  forwardDirectional->updateUniformDirectionalLight("directionalLight", m_activeLight);

  scene->renderAll(forwardDirectional);

  glDepthFunc(GL_LESS);
  glDepthMask(GL_TRUE);
  glDisable(GL_BLEND);
}

void GLManager::createShaders(void)
{
  forwardAmbient = new Shader("forward-ambient");
  forwardAmbient->setAttribLocation("position", 0);
  forwardAmbient->setAttribLocation("texCoord", 1);
  forwardAmbient->link();

  forwardAmbient->createUniform("ViewProj");
  forwardAmbient->createUniform("World");
  forwardAmbient->createUniform("ambientIntensity");

  forwardAmbient->createUniform("diffuseMap");

  forwardAmbient->setUniform1i("diffuseMap", 0);

  forwardAmbient->setUniformVec3f("ambientIntensity", glm::vec3(0.2f, 0.2f, 0.2f));

  forwardDirectional = new Shader("forward-directional");
  forwardDirectional->setAttribLocation("position", 0);
  forwardDirectional->setAttribLocation("texCoord", 1);
  forwardDirectional->setAttribLocation("normal", 2);
  forwardDirectional->link();

  forwardDirectional->createUniform("ViewProj");
  forwardDirectional->createUniform("World");

  forwardDirectional->createUniform("eyePos");
  forwardDirectional->createUniform("specularIntensity");
  forwardDirectional->createUniform("specularPower");

  forwardDirectional->createUniform("directionalLight.direction");
  forwardDirectional->createUniform("directionalLight.base.color");
  forwardDirectional->createUniform("directionalLight.base.intensity");

  forwardDirectional->createUniform("diffuseMap");
  forwardDirectional->createUniform("normalMap");
  forwardDirectional->createUniform("specularMap");

  forwardDirectional->setUniform1i("diffuseMap", 0);
  forwardDirectional->setUniform1i("normalMap", 1);
  forwardDirectional->setUniform1i("specularMap", 2);
}
