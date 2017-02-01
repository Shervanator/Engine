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

class TextureData
{
public:
  TextureData(int width, int height, const unsigned char* data, GLenum textureTarget, GLfloat filter);
  virtual ~TextureData(void);

  void createTexture(int width, int height, const unsigned char* data, GLenum textureTarget, GLfloat filter);
  void bind(unsigned int unit) const;

private:
  GLenum m_textureTarget;
  GLuint m_textureId;
};
