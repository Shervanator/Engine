#include <fstream>
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

#include "GLManager.h"

#include "Vertex.h"

GLManager::GLManager(int width, int height)
{
  Vertex vertices[] =
  {
    Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 0), glm::vec3(0, 0, -1)),
    Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 0, -1)),
    Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 0, -1)),
    Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(0, 0, -1)),

    Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(0, 0, 1)),
    Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(0, 0, 1)),
    Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 1), glm::vec3(0, 0, 1)),
    Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 1), glm::vec3(0, 0, 1)),

    Vertex(glm::vec3(-1, -1, -1), glm::vec2(0, 1), glm::vec3(0, -1, 0)),
    Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 1), glm::vec3(0, -1, 0)),
    Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(0, -1, 0)),
    Vertex(glm::vec3(1, -1, -1), glm::vec2(0, 0), glm::vec3(0, -1, 0)),

    Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 1, 0)),
    Vertex(glm::vec3(-1, 1, 1), glm::vec2(1, 1), glm::vec3(0, 1, 0)),
    Vertex(glm::vec3(1, 1, 1), glm::vec2(1, 0), glm::vec3(0, 1, 0)),
    Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 1, 0)),

    Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 1), glm::vec3(-1, 0, 0)),
    Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(-1, 0, 0)),
    Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(-1, 0, 0)),
    Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(-1, 0, 0)),

    Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(1, 0, 0)),
    Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(1, 0, 0)),
    Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 0), glm::vec3(1, 0, 0)),
    Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(1, 0, 0)),
  };

  unsigned int indices[] = {
    0, 1, 2,
    0, 2, 3,

    6, 5, 4,
    7, 6, 4,

    10, 9, 8,
    11, 10, 8,

    12, 13, 14,
    12, 14, 15,

    16, 17, 18,
    16, 18, 19,

    22, 21, 20,
    23, 22, 20};

  // model = new Mesh(vertices, sizeof(vertices) / sizeof(Vertex), indices, sizeof(indices) / sizeof(unsigned int));
  model = new Mesh("monkey3.obj");
  texture = new Texture("/Users/shervinaflatooni/Git/Engine/Engine/t.jpg");

  glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
  glClearDepth(1.0f);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glEnable(GL_CULL_FACE);

  glViewport(0, 0, width, height);

  createShaders();
  texture->bind(0);
}

GLManager::~GLManager(void)
{
  delete shader1;
  delete shader2;
  delete model;
  delete texture;
}

void GLManager::setViewProjection(const glm::mat4& viewProj)
{
  this->viewProj = viewProj;
}

void GLManager::tick(int delta_time)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  static float angle_in_degrees = 0.0f;
  angle_in_degrees += delta_time * 0.03;

  glm::mat4 Model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)) * glm::rotate(glm::mat4(1.0f), angle_in_degrees, glm::vec3(0, 1, 0));

  glm::mat4 MVP = viewProj * Model;

  glUniformMatrix4fv(shader1->getUniformLocation("MVP"), 1, GL_FALSE, &MVP[0][0]);
  model->render();

  // for (int i = 0; i < 10; i+=3)
  // {
  //   for (int j = 0; j < 10; j+=3)
  //   {
  //     for (int k = 0; k < 10; k+=3)
  //     {
  //       glm::mat4 Model = glm::mat4(1.0f);
  //       Model = glm::translate(glm::mat4(1.0f), glm::vec3(i, j, k)) * glm::rotate(Model, angle_in_degrees, glm::vec3(0, 1, 0));

  //       glm::mat4 MVP = viewProj * Model;

  //       glUniformMatrix4fv(shader1->getUniformLocation("MVP"), 1, GL_FALSE, &MVP[0][0]);
  //       model->render();
  //     }
  //   }
  // }
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
