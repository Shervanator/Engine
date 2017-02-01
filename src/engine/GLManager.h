//
//  Author: Shervin Aflatooni
//

#pragma once

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
#include "Window.h"
#include "components/Camera.h"

#include "components/DirectionalLight.h"
#include "components/PointLight.h"
#include "components/SpotLight.h"

#include "Line.h"

class GLManager
{
public:
  GLManager(const Window *window);
  ~GLManager(void);

  void bindRenderTarget(void) const;
  void renderScene(Entity *entity);
  void setActiveCamera(std::shared_ptr<Camera> camera);
  void addDirectionalLight(std::shared_ptr<DirectionalLight> light);
  void addPointLight(std::shared_ptr<PointLight> light);
  void addSpotLight(std::shared_ptr<SpotLight> light);

  void removeDirectionalLight(std::shared_ptr<DirectionalLight> light);
  void removePointLight(std::shared_ptr<PointLight> light);
  void removeSpotLight(std::shared_ptr<SpotLight> light);

  glm::mat4 getViewMatrix(void);
  glm::mat4 getProjectionMatrix(void);

  void drawEntity(Entity *entity);
  void drawLine(Line line);

  int width, height;

  GLuint lineBuffer;
  GLuint VertexArrayID;
private:
  void createShaders(void);

  void renderLights(Entity *scene);

  std::unique_ptr<Shader> m_simple;
  std::unique_ptr<Shader> m_forwardAmbient;
  std::unique_ptr<Shader> m_forwardDirectional;
  std::unique_ptr<Shader> m_forwardPoint;
  std::unique_ptr<Shader> m_forwardSpot;

  std::shared_ptr<Camera> m_activeCamera;

  std::vector<std::shared_ptr<DirectionalLight>> m_directionalLights;
  std::vector<std::shared_ptr<PointLight>> m_pointLights;
  std::vector<std::shared_ptr<SpotLight>> m_spotLights;
};
