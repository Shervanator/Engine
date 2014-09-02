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
  delete shader1;
}

void GLManager::setViewProjection(const glm::mat4& viewProj)
{
  this->viewProj = viewProj;
}

void GLManager::renderScene(Entity *entity)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUniformMatrix4fv(shader1->getUniformLocation("ViewProj"), 1, GL_FALSE, &viewProj[0][0]);

  entity->renderAll(shader1);
}

void GLManager::createShaders(void)
{
#if defined(GLES2) || defined(GLES3)
  shader1 = new Shader(Asset("shader0.vs"), Asset("shader0.fs"));
#else
  shader1 = new Shader(Asset("shader1.vs"), Asset("shader1.fs"));
#endif

  shader1->setAttribLocation("vertexPosition_modelspace", 0);
  shader1->setAttribLocation("texCoord", 1);
  shader1->setAttribLocation("normal", 2);
  shader1->setAttribLocation("tangent", 3);
  shader1->link();

  shader1->createUniform("ViewProj");
  shader1->createUniform("Model");


  shader1->bind();
}
