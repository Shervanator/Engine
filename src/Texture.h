#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

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
