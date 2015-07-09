//
//  Author: Shervin Aflatooni
//

#include "TextureData.h"

TextureData::TextureData(int width, int height, unsigned char* data, GLenum type, GLenum textureTarget, GLfloat filter)
{
  m_width = width;
  m_height = height;
  m_textureTarget = textureTarget;
  m_type = type;

  createTexture(data, filter);
}

TextureData::~TextureData()
{
  glDeleteTextures(1, &m_textureId);
}

void TextureData::createTexture(unsigned char* data, GLfloat filter)
{
  glGenTextures(1, &m_textureId);
  glBindTexture(m_textureTarget, m_textureId);

  glTexParameterf(m_textureTarget, GL_TEXTURE_MIN_FILTER, filter);
  glTexParameterf(m_textureTarget, GL_TEXTURE_MAG_FILTER, filter);

  glTexImage2D(m_textureTarget, 0, m_type, m_width, m_height, 0, m_type, GL_UNSIGNED_BYTE, data);
}

void TextureData::updateTexture(unsigned char* data)
{
  glBindTexture(m_textureTarget, m_textureId);
  glTexSubImage2D(m_textureTarget, 0, 0, 0, m_width, m_height, m_type, GL_UNSIGNED_BYTE, data);
}

void TextureData::bind(unsigned int unit)
{
  glActiveTexture(GL_TEXTURE0 + unit);
  glBindTexture(m_textureTarget, m_textureId);
}


int TextureData::getWidth(void) {
  return m_width;
}

int TextureData::getHeight(void) {
  return m_height;
}
