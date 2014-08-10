#ifndef TEXTURE_H
#define TEXTURE_H

#ifndef EMSCRIPTEN
  #include <GL/glew.h>
#else
  #include <GLES2/gl2.h>
  #include <GLES2/gl2ext.h>
#endif

class Texture
{
public:
  Texture(const char* file);
  ~Texture(void);

  void bind(unsigned int unit);

private:
  GLuint textureId;
};

#endif
