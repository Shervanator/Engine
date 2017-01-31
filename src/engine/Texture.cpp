//
//  Author: Shervin Aflatooni
//

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Texture.h"
#include "Logger.h"

#include <map>

std::map<std::string, std::weak_ptr<TextureData>> m_textureCache;

Texture::Texture(const Asset &file, GLenum textureTarget, GLfloat filter)
{
  auto it = m_textureCache.find(file.getIOStream()->getFileName());

  if(it == m_textureCache.end() || !(m_textureData = it->second.lock())) {
    int x, y, bytesPerPixel;
    unsigned char* data = stbi_load_from_memory(reinterpret_cast<const unsigned char *>(file.read()), file.getIOStream()->fileSize(), &x, &y, &bytesPerPixel, 4);

    if (data == NULL) {
      log_err("Unable to load texture: %s", file.getIOStream()->getFileName().c_str());
    }
    else {
      m_textureData = std::make_shared<TextureData>(x, y, data, textureTarget, filter);
      m_textureCache[file.getIOStream()->getFileName()] = m_textureData;
      stbi_image_free(data);
    }
  }
}

Texture::~Texture()
{
}

void Texture::bind(unsigned int unit) const
{
  m_textureData->bind(unit);
}
