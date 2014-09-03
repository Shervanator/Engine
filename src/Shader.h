#ifndef SHADER_H
#define SHADER_H

#include <map>
#include <string>

#include <glm/glm.hpp>

#include "Asset.h"

class DirectionalLight;

#if defined(GLES2)
  #include <GLES2/gl2.h>
#elif defined(GLES3)
  #include <GLES3/gl3.h>
#else
  #include <GL/glew.h>
#endif

class Shader
{
public:
  Shader(void);
  Shader(Asset vertexSrc, Asset fragmentSrc);
  Shader(const char* vert_src, const char* frag_src);
  ~Shader(void);

  void addVertex(const char *vert_src);
  void addFragment(const char *frag_src);
  void link(void);

  void createUniform(const std::string& uniformName);
  GLuint getUniformLocation(const std::string& uniformName);

  void setAttribLocation(const char* name, int i);

  GLuint getProgram(void);

  void bind(void);

  void updateUniformDirectionalLight(const std::string &uniformName, DirectionalLight *directionalLight);

  void setUniformVec3f(const std::string &uniformName, glm::vec3 vector);
  void setUniform1f(const std::string &uniformName, float value);
private:
  GLuint  g_shVert;
  GLuint  g_shFrag;
  GLuint  g_shProg;

  std::map <std::string, GLuint> uniformLocation;
};

#endif
