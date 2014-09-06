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

#include <vector>

#include "Shader.h"
#include "Entity.h"
#include "Camera.h"

#include "BaseLight.h"

class GLManager
{
public:
  GLManager(int width, int height);
  ~GLManager(void);

  void renderScene(Entity *entity);
  void setActiveCamera(Camera *camera);
  void addLight(BaseLight *light);

  int width, height;
private:
  void createShaders(void);

  Shader *forwardAmbient;
  Shader *forwardDirectional;
  Shader *forwardPoint;
  Shader *forwardSpot;

  Camera *m_activeCamera;

  std::vector<BaseLight *> m_lights;
};

#endif
