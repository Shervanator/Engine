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

  transformStack.push(glm::mat4(1));
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

  glUniformMatrix4fv(shader1->getUniformLocation("ViewProj"), 1, GL_FALSE, &viewProj[0][0]);

  recursiveSceneRenderer(scene);
}

void GLManager::recursiveSceneRenderer(SceneNode *scene)
{
  // compute current transform
  glm::mat4 currentTransform = transformStack.top() * scene->getTransform().getTransformMatrix();

  // push scene transform matrix to stack
  transformStack.push(currentTransform);

  // set shader to transform to current location.
  glUniformMatrix4fv(shader1->getUniformLocation("Model"), 1, GL_FALSE, &currentTransform[0][0]);

  // render this current scene
  scene->render(shader1);

  // recursive render children with this function
  for (unsigned int i = 0; i < scene->getChildren()->size(); i++)
  {
    recursiveSceneRenderer(scene->getChildren()->at(i));
  }

  // pop scene transform
  transformStack.pop();
}

void GLManager::createShaders(void)
{
  shader1 = new Shader("res/shader1");

  shader1->createUniform("ViewProj");
  shader1->createUniform("Model");

  shader1->bind();
}
