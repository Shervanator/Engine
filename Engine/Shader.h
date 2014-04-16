#ifndef SHADER_H
#define SHADER_H

#include <map>

#include <glm/glm.hpp>
#include <GL/glew.h>

class Shader
{
public:
  Shader(void);
  Shader(const char* vert_src, const char* frag_src);
  ~Shader(void);

  void addVertex(const char* vert_src);
  void addFragment(const char* frag_src);
  void link(void);

  void createUniform(const char* uniform_name);
  void setUniformMat4(const char* uniform_name, glm::mat4 & value);

  GLuint getProgram(void);
  GLuint getMVPLocation(void);
private:
  GLuint  g_shVert;
  GLuint  g_shFrag;
  GLuint  g_shProg;

  GLuint mvp_uni;

  std::map <const char*, GLuint> uniform_location;
};

#endif
