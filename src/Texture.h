//
//  Author: Shervin Aflatooni
//

#ifndef TEXTURE_H
#define TEXTURE_H

#if defined(GLES2)
  #include <GLES2/gl2.h>
#elif defined(GLES3)
  #include <GLES3/gl3.h>
#else
  #include <GL/glew.h>
#endif

#include "Asset.h"
#include "TextureData.h"

class Texture
{
public:
  Texture(Asset file, GLenum textureTarget = GL_TEXTURE_2D, GLfloat filter = GL_LINEAR);
  Texture(TextureData *data);
  ~Texture(void);

  TextureData *getTextureData(void);

  void bind(unsigned int unit = 0);

private:
  TextureData *m_textureData;
};

#endif
