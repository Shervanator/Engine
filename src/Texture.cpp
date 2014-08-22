#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Texture.h"
#include "Logger.h"

Texture::Texture(Asset file, GLenum textureTarget, GLfloat filter)
{
  int x, y, bytesPerPixel;
  unsigned char* data = stbi_load_from_memory(reinterpret_cast<const unsigned char *>(file.read()), file.getSize(), &x, &y, &bytesPerPixel, 4);

  if(data == NULL) {
    log_err("Unable to load texture: %s", file.getFileName().c_str());
  } else {
    initTexture(x,y,data,textureTarget,filter);
    stbi_image_free(data);
  }
}

void Texture::initTexture(int width, int height, unsigned char* data, GLenum textureTarget, GLfloat filter)
{
  this->textureTarget = textureTarget;

  glGenTextures(1, &textureId);
  glBindTexture(textureTarget, textureId);
  glTexParameterf(textureTarget, GL_TEXTURE_MIN_FILTER, filter);
  glTexParameterf(textureTarget, GL_TEXTURE_MAG_FILTER, filter);
  glTexImage2D(textureTarget, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}

Texture::~Texture()
{
  glDeleteTextures(1, &textureId);
}

void Texture::bind(unsigned int unit)
{
  glActiveTexture(GL_TEXTURE0 + unit);
  glBindTexture(textureTarget, textureId);
}
