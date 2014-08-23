#ifndef GL_MANAGER_H
#define GL_MANAGER_H

#include <glm/glm.hpp>

#if defined(GLES2)
  #include <GLES2/gl2.h>
#elif defined(GLES3)
  #include <GLES3/gl3.h>
#else
  #include <GL/glew.h>
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
