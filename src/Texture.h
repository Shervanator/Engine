#ifndef TEXTURE_H
#define TEXTURE_H

#if defined(GLES2)
  #include <GLES2/gl2.h>
#else
  #include <GL/glew.h>
#endif

class Texture
{
public:
  Texture(const std::string& file, GLenum textureTarget = GL_TEXTURE_2D, GLfloat filter = GL_LINEAR);
  ~Texture(void);

  void bind(unsigned int unit = 0);

private:
  void initTexture(int width, int height, unsigned char* data, GLenum textureTarget, GLfloat filter);

  GLenum textureTarget;
  GLuint textureId;
};

#endif
