//
//  Author: Shervin Aflatooni
//

#pragma once

#if defined(GLES2)
  #include <GLES2/gl2.h>
#elif defined(GLES3)
  #include <GLES3/gl3.h>
#else
  #include <GL/glew.h>
#endif

#include "Asset.h"
#include "TextureData.h"

#include <memory>

class Texture
{
public:
  Texture(const Asset &file, GLenum textureTarget = GL_TEXTURE_2D, GLfloat filter = GL_LINEAR);
  ~Texture(void);

  void bind(unsigned int unit = 0) const;

private:
  std::shared_ptr<TextureData> m_textureData;
};
