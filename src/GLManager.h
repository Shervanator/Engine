#ifndef GL_MANAGER_H
#define GL_MANAGER_H

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

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

class GLManager
{
public:
  GLManager(int width, int height);
  ~GLManager(void);

  void renderScene(Entity *entity);
  void setActiveCamera(Camera *camera);
  void addDirectionalLight(DirectionalLight *light);
  void addPointLight(PointLight *light);
  void addSpotLight(SpotLight *light);

  int width, height;
private:
  void createShaders(void);

  void renderLights(std::vector<BaseLight *> &lights, Shader *shader, Entity *scene);

  Shader *forwardAmbient;
  Shader *forwardDirectional;
  Shader *forwardPoint;
  Shader *forwardSpot;

  Camera *m_activeCamera;

  std::vector<BaseLight *> m_directionalLights;
  std::vector<BaseLight *> m_pointLights;
  std::vector<BaseLight *> m_spotLights;
};

#endif
