#include "GLManager.h"

GLManager::GLManager(int width, int height)
{
  glClearColor(0.0f, 0.0f, 0.4f, 1.0f);

  glClearDepthf(1.0f);
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
#if defined(GLES2)
  shader1 = new Shader(Asset("shader0.vs"), Asset("shader0.fs"));
#else
  shader1 = new Shader(Asset("shader1.vs"), Asset("shader1.fs"));
#endif

  shader1->createUniform("ViewProj", 0);
  shader1->createUniform("Model", 1);

  shader1->bind();
}
