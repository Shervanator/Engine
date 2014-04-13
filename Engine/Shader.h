#ifndef SHADER_H
#define SHADER_H

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
  GLuint getProgram(void);
  GLuint getMVPLocation(void);
private:
  GLuint  g_shVert;
  GLuint  g_shFrag;
  GLuint  g_shProg;

  GLuint mvp_uni;
};

#endif
