#include <fstream>
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

#include "GLManager.h"

GLManager::GLManager(void)
{
}

GLManager::~GLManager(void)
{
}

void GLManager::clean(void)
{
  delete shader1;
  delete shader2;
  delete model;
}

int GLManager::init(const int width, const int height)
{
  model = new Model();
  glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
  glClearDepth(1.0f);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glEnable(GL_CULL_FACE);

  glViewport(0, 0, width, height);

  projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

  createShaders();

  return 0;
}

void GLManager::setLookAt(glm::vec3 position, glm::vec3 direction, glm::vec3 up)
{
  view = glm::lookAt( position, direction, up );
}

void GLManager::tick(int delta_time)
{
  glm::mat4 Model = glm::mat4(1.0f);
  static float angle_in_degrees = 0.0f;
  angle_in_degrees += delta_time * 0.01;
  Model = glm::rotate(Model, angle_in_degrees, glm::vec3(0, 1, 0));
  glm::mat4 MVP   = projection * view * Model;

  glUniformMatrix4fv(shader1->getUniformLocation("MVP"), 1, GL_FALSE, &MVP[0][0]);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  model->render();
}

void GLManager::createShaders(void)
{
  std::ifstream in("shader1.vert");
  std::string vert_src((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

  std::ifstream in2("shader1.frag");
  std::string frag_src((std::istreambuf_iterator<char>(in2)), std::istreambuf_iterator<char>());

  std::ifstream in3("shader2.frag");
  std::string frag_src2((std::istreambuf_iterator<char>(in3)), std::istreambuf_iterator<char>());

  shader1 = new Shader(vert_src.c_str(), frag_src.c_str());
  shader2 = new Shader(vert_src.c_str(), frag_src2.c_str());

  shader1->createUniform("MVP");

  glUseProgram(shader1->getProgram());
}
