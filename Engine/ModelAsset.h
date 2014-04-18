#ifndef MODEL_ASSET_H
#define MODEL_ASSET_H

#include <GL/glew.h>
#include <glm/glm.hpp>

class ModelAsset
{
public:
  ModelAsset(void);
  ~ModelAsset(void);

  void render(void);

private:
  GLuint  g_vao;
  GLuint  g_vbo;

  glm::vec3 position;
};

#endif
