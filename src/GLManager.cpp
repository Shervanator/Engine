#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

#include "GLManager.h"

#include "Vertex.h"

GLManager::GLManager(int width, int height)
{
  glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
  glClearDepth(1.0f);

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

  glm::mat4 Model = glm::mat4(1.0f);

  glm::mat4 MVP = viewProj * Model;

  glUniformMatrix4fv(shader1->getUniformLocation("MVP"), 1, GL_FALSE, &MVP[0][0]);

  scene->render();
}

void GLManager::createShaders(void)
{
  shader1 = new Shader("res/shader1");

  shader1->createUniform("MVP");

  glUseProgram(shader1->getProgram());
}
