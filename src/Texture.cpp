//
//  Author: Shervin Aflatooni
//

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Texture.h"
#include "Logger.h"

#include <map>

std::map<std::string, TextureData *> m_textureCache;

Texture::Texture(Asset file, GLenum textureTarget, GLfloat filter)
{
  std::map<std::string, TextureData *>::const_iterator it = m_textureCache.find(file.getIOStream()->getFileName().c_str());

  if(it != m_textureCache.end()) {
    m_textureData = it->second;
    m_textureData->incrementReference();
  } else {
    int x, y, bytesPerPixel;
    unsigned char* data = stbi_load_from_memory(reinterpret_cast<const unsigned char *>(file.read()), file.getIOStream()->fileSize(), &x, &y, &bytesPerPixel, 4);

    if(data == NULL) {
      log_err("Unable to load texture: %s", file.getIOStream()->getFileName().c_str());
    } else {
      m_textureData = m_textureCache[file.getIOStream()->getFileName().c_str()] = new TextureData(x, y, data, GL_RGBA, textureTarget, filter);
      stbi_image_free(data);
      m_textureData->incrementReference();
    }
  }
}

Texture::Texture(TextureData *data) {
  m_textureData = data;
  m_textureData->incrementReference();
}

Texture::~Texture()
{
  // TODO: DELETE TEXTURE FROM CACHE IF IT IS LAST REFERENCE..
  m_textureData->decrementReference();
}

TextureData *Texture::getTextureData(void) {
  return m_textureData;
}

void Texture::bind(unsigned int unit)
{
  m_textureData->bind(unit);
}
