#include "GLManager.h"

GLManager::GLManager(int width, int height)
{
  glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
#ifndef EMSCRIPTEN
  glClearDepth(1.0f);
#else
  glClearDepthf(1.0f);
#endif
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glEnable(GL_CULL_FACE);

  glViewport(0, 0, width, height);

  createShaders();
}

GLManager::~GLManager(void)
{
  delete shader1;
}

void GLManager::setViewProjection(const glm::mat4& viewProj)
{
  this->viewProj = viewProj;
}

void GLManager::renderScene(SceneNode *scene)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUniformMatrix4fv(shader1->getUniformLocation("ViewProj", 0), 1, GL_FALSE, &viewProj[0][0]);

  scene->renderAll(shader1);
}

void GLManager::createShaders(void)
{
#ifndef EMSCRIPTEN
  shader1 = new Shader("../assets/shader1");
#else
  shader1 = new Shader("../assets/shader0");
#endif
  shader1->createUniform("ViewProj", 0);
  shader1->createUniform("Model", 1);

  shader1->bind();
}
