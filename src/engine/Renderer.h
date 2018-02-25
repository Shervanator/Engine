//
//  Author: Shervin Aflatooni
//

#pragma once

#include <vector>

#include "Entity.h"
#include "components/Camera.h"
#include "components/PointLight.h"
#include "components/DirectionalLight.h"
#include "components/SpotLight.h"

class Renderer
{
public:
  virtual ~Renderer();

  virtual void render(const Entity &scene, std::shared_ptr<Camera> activeCamera, const std::vector<std::shared_ptr<PointLight>> &pointLights, const std::vector<std::shared_ptr<DirectionalLight>> &directionalLights, const std::vector<std::shared_ptr<SpotLight>> &spotLights) const = 0;
};
