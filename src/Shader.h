#ifndef SHADER_H
#define SHADER_H

#include <map>
#include <string>

#include <glm/glm.hpp>
#ifndef EMSCRIPTEN
  #include <GL/glew.h>
#else
  #include <GLES2/gl2.h>
  #include <GLES2/gl2ext.h>
#endif

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

  void bind(void);
private:
  GLuint  g_shVert;
  GLuint  g_shFrag;
  GLuint  g_shProg;

  std::map <const char*, GLuint> uniform_location;
};

#endif
