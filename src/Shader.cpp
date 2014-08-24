#include "Shader.h"
#include "Logger.h"

Shader::Shader(void)
{
  g_shProg = glCreateProgram();
}

Shader::Shader(Asset vertexSrc, Asset fragmentSrc)
{
  g_shProg = glCreateProgram();

  addVertex(vertexSrc.read());
  addFragment(fragmentSrc.read());
}

Shader::Shader(const char* vert_src, const char* frag_src)
{
  g_shProg = glCreateProgram();
  addVertex(vert_src);
  addFragment(frag_src);
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
    glGetShaderInfoLog(g_shVert, 1024, &errlen, shErr);
    log_err("Failed to compile vertex shader: %s", shErr);
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
    glGetShaderInfoLog(g_shFrag, 1024, &errlen, shErr);
    log_err("Failed to compile fragment shader: %s", shErr);
    return;
  }

  // Attach these shaders to the shader program
  glAttachShader(g_shProg, g_shFrag);

  // flag the shaders to be deleted when the shader program is deleted
  glDeleteShader(g_shFrag);
}

void Shader::link(void)
{
  char shErr[1024];
  int errlen;
  GLint res;
  // Link the shaders
  glLinkProgram(g_shProg);
  glGetProgramiv(g_shProg, GL_LINK_STATUS, &res);

  if (GL_FALSE == res)
    log_err("Failed to link shader program");

  glValidateProgram(g_shProg);
  glGetProgramiv(g_shProg, GL_VALIDATE_STATUS, &res);
  if (GL_FALSE == res) {
    glGetProgramInfoLog(g_shProg, 1024, &errlen, shErr);
    log_err("Error validating shader: %s", shErr);
  }
}

GLuint Shader::getProgram(void)
{
  return g_shProg;
}

void Shader::createUniform(const char* uniform_name, int i)
{
  uniform_location[i] = glGetUniformLocation(g_shProg, uniform_name);
}

GLuint Shader::getUniformLocation(const char* uniform_name, int i)
{
  return uniform_location[i];
}

void Shader::setAttribLocation(const char* name, int i)
{
  glBindAttribLocation(g_shProg, i, name);
}

void Shader::bind(void)
{
  glUseProgram(g_shProg);
}
