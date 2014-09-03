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
#if !defined(GLES2) && !defined(GLES3)
  delete forwardDirectional;
#endif
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

  forwardAmbient->bind();
  glUniformMatrix4fv(forwardAmbient->getUniformLocation("ViewProj"), 1, GL_FALSE, &(m_activeCamera->getViewProjection())[0][0]);

  scene->renderAll(forwardAmbient);

  glEnable(GL_BLEND);
  glBlendFunc(GL_ONE, GL_ONE);
  glDepthMask(GL_FALSE);
  glDepthFunc(GL_EQUAL);

  forwardDirectional->bind();
  glUniformMatrix4fv(forwardDirectional->getUniformLocation("ViewProj"), 1, GL_FALSE, &(m_activeCamera->getViewProjection())[0][0]);
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
#if defined(GLES2) || defined(GLES3)
  forwardAmbient = new Shader(Asset("shader0.vs"), Asset("shader0.fs"));
  forwardAmbient->setAttribLocation("position", 0);
  forwardAmbient->setAttribLocation("texCoord", 1);
  forwardAmbient->link();

  forwardAmbient->createUniform("ViewProj");
  forwardAmbient->createUniform("World");
#else
  forwardAmbient = new Shader(Asset("forward-ambient.vs"), Asset("forward-ambient.fs"));
  forwardAmbient->setAttribLocation("position", 0);
  forwardAmbient->setAttribLocation("texCoord", 1);
  forwardAmbient->link();

  forwardAmbient->createUniform("ViewProj");
  forwardAmbient->createUniform("World");
  forwardAmbient->createUniform("ambientIntensity");

  forwardAmbient->bind();

  glUniform3f(forwardAmbient->getUniformLocation("ambientIntensity"), 0.2f, 0.2f, 0.2f);

  forwardDirectional = new Shader(Asset("forward-directional.vs"), Asset("forward-directional.fs"));
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

  forwardDirectional->bind();
#endif
}
