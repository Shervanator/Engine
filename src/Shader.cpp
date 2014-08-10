#include <iostream>
#include <fstream>

#include "Shader.h"

Shader::Shader(void)
{
  g_shProg = glCreateProgram();
}

Shader::Shader(std::string shaderFile)
{
  std::ifstream in(shaderFile + ".vs");
  std::string vert_src((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

  std::ifstream in2(shaderFile + ".fs");
  std::string frag_src((std::istreambuf_iterator<char>(in2)), std::istreambuf_iterator<char>());

  g_shProg = glCreateProgram();

  addVertex(vert_src.c_str());
  addFragment(frag_src.c_str());
  link();
}

Shader::Shader(const char* vert_src, const char* frag_src)
{
  g_shProg = glCreateProgram();
  addVertex(vert_src);
  addFragment(frag_src);
  link();
}

Shader::~Shader(void)
{
  glDeleteProgram(g_shProg);
}

void Shader::addVertex(const char* vert_src)
{
  char shErr[1024];
  int errlen;
  GLint res;

  // Generate some IDs for our shader programs
  g_shVert = glCreateShader(GL_VERTEX_SHADER);

  // Assign our above shader source code to these IDs
  glShaderSource(g_shVert, 1, &vert_src, nullptr);

  // Attempt to compile the source code
  glCompileShader(g_shVert);

  // check if compilation was successful
  glGetShaderiv(g_shVert, GL_COMPILE_STATUS, &res);
  if (GL_FALSE == res){
    fprintf(stderr, "Failed to compile vertex shader\n");
    glGetShaderInfoLog(g_shVert, 1024, &errlen, shErr);
    printf("%s\n", shErr);
    return;
  }

  // Attach these shaders to the shader program
  glAttachShader(g_shProg, g_shVert);

  // flag the shaders to be deleted when the shader program is deleted
  glDeleteShader(g_shVert);
}

void Shader::addFragment(const char* frag_src)
{
  char shErr[1024];
  int errlen;
  GLint res;

  // Generate some IDs for our shader programs
  g_shFrag = glCreateShader(GL_FRAGMENT_SHADER);

  // Assign our above shader source code to these IDs
  glShaderSource(g_shFrag, 1, &frag_src, nullptr);

  // Attempt to compile the source code
  glCompileShader(g_shFrag);

  // check if compilation was successful
  glGetShaderiv(g_shFrag, GL_COMPILE_STATUS, &res);
  if (GL_FALSE == res){
    fprintf(stderr, "Failed to compile fragment shader\n");
    glGetShaderInfoLog(g_shFrag, 1024, &errlen, shErr);
    printf("%s\n", shErr);
    return;
  }

  // Attach these shaders to the shader program
  glAttachShader(g_shProg, g_shFrag);

  // flag the shaders to be deleted when the shader program is deleted
  glDeleteShader(g_shFrag);
}

void Shader::link(void)
{
  GLint res;
  // Link the shaders
  glLinkProgram(g_shProg);
  glGetProgramiv(g_shProg, GL_LINK_STATUS, &res);

  if (GL_FALSE == res)
    fprintf(stderr, "Failed to link shader program\n");
}

GLuint Shader::getProgram(void)
{
  return g_shProg;
}

void Shader::createUniform(const char* uniform_name)
{
  uniform_location[uniform_name] = glGetUniformLocation(g_shProg, uniform_name);
}

GLuint Shader::getUniformLocation(const char* uniform_name)
{
  return uniform_location[uniform_name];
}

void Shader::bind(void)
{
  glUseProgram(g_shProg);
}
