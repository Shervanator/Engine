#include <SOIL.h>
#include <iostream>

#include "Texture.h"

Texture::Texture(const char* file)
{
#ifndef EMSCRIPTEN
  textureId = SOIL_load_OGL_texture
  (
    file,
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_MIPMAPS | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_TEXTURE_REPEATS
  );

  if( 0 == textureId )
  {
    std::cerr << "SOIL loading error: " << SOIL_last_result() << std::endl;
  }
#endif
}

Texture::~Texture(void)
{
#ifndef EMSCRIPTEN
  glDeleteTextures(1, &textureId);
#endif
}

void Texture::bind(unsigned int unit)
{
#ifndef EMSCRIPTEN
  glActiveTexture(GL_TEXTURE0 + unit);
  glBindTexture(GL_TEXTURE_2D, textureId);
#endif
}
