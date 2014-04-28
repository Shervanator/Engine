#ifndef SHADER_H
#define SHADER_H

#include <map>
#include <string>

#include <glm/glm.hpp>
#include <GL/glew.h>

class Shader
{
public:
  Shader(void);
  Shader(std::string shaderFile);
  Shader(const char* vert_src, const char* frag_src);
  ~Shader(void);

  void addVertex(const char* vert_src);
  void addFragment(const char* frag_src);
  void link(void);

  void createUniform(const char* uniform_name);
  GLuint getUniformLocation(const char* uniform_name);

  GLuint getProgram(void);
private:
  GLuint  g_shVert;
  GLuint  g_shFrag;
  GLuint  g_shProg;

  std::map <const char*, GLuint> uniform_location;
};

#endif
