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
}

int GLManager::init(const int width, const int height)
{
  createVAO();
  glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
  glClearDepth(1.0f);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glEnable(GL_CULL_FACE);

  glViewport(0, 0, width, height);

  createVAO();
  createShaders();

  return 0;
}

void GLManager::setLookAt(glm::vec3 position, glm::vec3 direction, glm::vec3 up)
{
  view = glm::lookAt( position, direction, up );
}

void GLManager::tick(int delta_time)
{
  glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

  glm::mat4 Model = glm::mat4(1.0f);
  glm::mat4 MVP   = Projection * view * Model;

  glUniformMatrix4fv(shader1->getMVPLocation(), 1, GL_FALSE, &MVP[0][0]);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, g_vbo);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
   
  glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
   
  glDisableVertexAttribArray(0);
}

void GLManager::createVAO(void)
{
  static const GLfloat g_vertex_buffer_data[] = {
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
  };

  // Generate ID for VAO, and bind it as the active VAO
  glGenVertexArrays(1, &g_vao);
  glBindVertexArray(g_vao);

  // Generate a VBO to store our vertex list
  glGenBuffers(1, &g_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, g_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
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

  glUseProgram(shader1->getProgram());
}
