//
//  Author: Shervin Aflatooni
//

#pragma once

#include "Renderer.h"
#include "Shader.h"

class ForwardRenderer : public Renderer
{
public:
  ForwardRenderer();
  virtual ~ForwardRenderer();

  virtual void render(const Entity &scene, std::shared_ptr<Camera> activeCamera, const std::vector<std::shared_ptr<PointLight>> &pointLights, const std::vector<std::shared_ptr<DirectionalLight>> &directionalLights, const std::vector<std::shared_ptr<SpotLight>> &spotLights) const;

private:
  void createShaders();

  std::unique_ptr<Shader> m_forwardAmbient;
  std::unique_ptr<Shader> m_forwardDirectional;
  std::unique_ptr<Shader> m_forwardPoint;
  std::unique_ptr<Shader> m_forwardSpot;
};
