#include "GLManager.h"

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

void GLManager::setViewProjection(const glm::mat4& viewProj)
{
  this->viewProj = viewProj;
}

void GLManager::renderScene(Entity *scene)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  forwardAmbient->bind();
  glUniformMatrix4fv(forwardAmbient->getUniformLocation("ViewProj"), 1, GL_FALSE, &viewProj[0][0]);

  scene->renderAll(forwardAmbient);

  glEnable(GL_BLEND);
  glBlendFunc(GL_ONE, GL_ONE);
  glDepthMask(GL_FALSE);
  glDepthFunc(GL_EQUAL);

  // scene->renderAll(forwardDirectional);

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
  glUniform3f(forwardAmbient->getUniformLocation("ambientIntensity", 2), 1.0f, 1.0f, 1.0f);


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
#endif
}
