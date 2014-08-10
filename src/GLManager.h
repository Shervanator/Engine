#ifndef GL_MANAGER_H
#define GL_MANAGER_H

#include <glm/glm.hpp>
#ifndef EMSCRIPTEN
  #include <GL/glew.h>
#else
  #include <GLES2/gl2.h>
  #include <GLES2/gl2ext.h>
#endif

#include "Shader.h"
#include "SceneNode.h"

class GLManager
{
public:
  GLManager(int width, int height);
  ~GLManager(void);

  void renderScene(SceneNode *scene);
  void setViewProjection(const glm::mat4& viewProj);

private:
  void createShaders(void);

  Shader *shader1;

  glm::mat4 viewProj;
};

#endif
