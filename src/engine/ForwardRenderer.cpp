#include "ForwardRenderer.h"

ForwardRenderer::ForwardRenderer()
{
  createShaders();
}

ForwardRenderer::~ForwardRenderer()
{
}

void ForwardRenderer::render(const Entity &scene, std::shared_ptr<Camera> activeCamera, const std::vector<std::shared_ptr<PointLight>> &pointLights, const std::vector<std::shared_ptr<DirectionalLight>> &directionalLights, const std::vector<std::shared_ptr<SpotLight>> &spotLights) const
{
  m_forwardAmbient->setUniformMatrix4f("View", activeCamera->getViewMatrix());
  m_forwardAmbient->setUniformMatrix4f("Proj", activeCamera->getProjectionMatrix());

  scene.renderAll(m_forwardAmbient.get());

  glEnable(GL_BLEND);
  glBlendFunc(GL_ONE, GL_ONE);
  glDepthMask(GL_FALSE);
  glDepthFunc(GL_EQUAL);

  m_forwardDirectional->setUniformMatrix4f("View", activeCamera->getViewMatrix());
  m_forwardDirectional->setUniformMatrix4f("Proj", activeCamera->getProjectionMatrix());
  m_forwardDirectional->setUniformVec3f("eyePos", activeCamera->getParent()->getPosition());

  m_forwardDirectional->setUniform1f("specularIntensity", 0.5);
  m_forwardDirectional->setUniform1f("specularPower", 10);
  for (auto light : directionalLights)
  {
    light->updateShader(m_forwardDirectional.get());

    scene.renderAll(m_forwardDirectional.get());
  }

  m_forwardPoint->setUniformMatrix4f("View", activeCamera->getViewMatrix());
  m_forwardPoint->setUniformMatrix4f("Proj", activeCamera->getProjectionMatrix());
  m_forwardPoint->setUniformVec3f("eyePos", activeCamera->getParent()->getPosition());

  m_forwardPoint->setUniform1f("specularIntensity", 0.5);
  m_forwardPoint->setUniform1f("specularPower", 10);
  for (auto light : pointLights)
  {
    light->updateShader(m_forwardPoint.get());

    scene.renderAll(m_forwardPoint.get());
  }

  m_forwardSpot->setUniformMatrix4f("View", activeCamera->getViewMatrix());
  m_forwardSpot->setUniformMatrix4f("Proj", activeCamera->getProjectionMatrix());
  m_forwardSpot->setUniformVec3f("eyePos", activeCamera->getParent()->getPosition());

  m_forwardSpot->setUniform1f("specularIntensity", 0.5);
  m_forwardSpot->setUniform1f("specularPower", 10);
  for (auto light : spotLights)
  {
    light->updateShader(m_forwardSpot.get());

    scene.renderAll(m_forwardSpot.get());
  }

  glDepthFunc(GL_LESS);
  glDepthMask(GL_TRUE);
  glDisable(GL_BLEND);
}

void ForwardRenderer::createShaders()
{
  m_forwardAmbient = std::make_unique<Shader>("shaders/forward-ambient");
  m_forwardAmbient->setAttribLocation("position", 0);
  m_forwardAmbient->setAttribLocation("texCoord", 1);
  m_forwardAmbient->link();

  m_forwardAmbient->createUniform("View");
  m_forwardAmbient->createUniform("Proj");
  m_forwardAmbient->createUniform("World");
  m_forwardAmbient->createUniform("ambientIntensity");

  m_forwardAmbient->createUniform("diffuseMap");

  m_forwardAmbient->setUniform1i("diffuseMap", 0);

  m_forwardAmbient->setUniformVec3f("ambientIntensity", glm::vec3(0.2f, 0.2f, 0.2f));

  m_forwardDirectional = std::make_unique<Shader>("shaders/forward-directional");
  m_forwardDirectional->setAttribLocation("position", 0);
  m_forwardDirectional->setAttribLocation("texCoord", 1);
  m_forwardDirectional->setAttribLocation("normal", 2);
  m_forwardDirectional->setAttribLocation("tangent", 3);
  m_forwardDirectional->link();

  m_forwardDirectional->createUniform("View");
  m_forwardDirectional->createUniform("Proj");
  m_forwardDirectional->createUniform("World");

  m_forwardDirectional->createUniform("eyePos");
  m_forwardDirectional->createUniform("specularIntensity");
  m_forwardDirectional->createUniform("specularPower");

  m_forwardDirectional->createUniform("directionalLight.base.color");
  m_forwardDirectional->createUniform("directionalLight.base.intensity");

  m_forwardDirectional->createUniform("directionalLight.direction");

  m_forwardDirectional->createUniform("diffuseMap");
  m_forwardDirectional->createUniform("normalMap");
  m_forwardDirectional->createUniform("specularMap");

  m_forwardDirectional->setUniform1i("diffuseMap", 0);
  m_forwardDirectional->setUniform1i("normalMap", 1);
  m_forwardDirectional->setUniform1i("specularMap", 2);

  m_forwardPoint = std::make_unique<Shader>("shaders/forward-point");
  m_forwardPoint->setAttribLocation("position", 0);
  m_forwardPoint->setAttribLocation("texCoord", 1);
  m_forwardPoint->setAttribLocation("normal", 2);
  m_forwardPoint->setAttribLocation("tangent", 3);
  m_forwardPoint->link();

  m_forwardPoint->createUniform("View");
  m_forwardPoint->createUniform("Proj");
  m_forwardPoint->createUniform("World");

  m_forwardPoint->createUniform("eyePos");
  m_forwardPoint->createUniform("specularIntensity");
  m_forwardPoint->createUniform("specularPower");

  m_forwardPoint->createUniform("pointLight.base.color");
  m_forwardPoint->createUniform("pointLight.base.intensity");

  m_forwardPoint->createUniform("pointLight.attenuation.constant");
  m_forwardPoint->createUniform("pointLight.attenuation.linear");
  m_forwardPoint->createUniform("pointLight.attenuation.exponent");

  m_forwardPoint->createUniform("pointLight.position");
  m_forwardPoint->createUniform("pointLight.range");

  m_forwardPoint->createUniform("diffuseMap");
  m_forwardPoint->createUniform("normalMap");
  m_forwardPoint->createUniform("specularMap");

  m_forwardPoint->setUniform1i("diffuseMap", 0);
  m_forwardPoint->setUniform1i("normalMap", 1);
  m_forwardPoint->setUniform1i("specularMap", 2);

  m_forwardSpot = std::make_unique<Shader>("shaders/forward-spot");
  m_forwardSpot->setAttribLocation("position", 0);
  m_forwardSpot->setAttribLocation("texCoord", 1);
  m_forwardSpot->setAttribLocation("normal", 2);
  m_forwardSpot->setAttribLocation("tangent", 3);
  m_forwardSpot->link();

  m_forwardSpot->createUniform("View");
  m_forwardSpot->createUniform("Proj");
  m_forwardSpot->createUniform("World");

  m_forwardSpot->createUniform("eyePos");
  m_forwardSpot->createUniform("specularIntensity");
  m_forwardSpot->createUniform("specularPower");

  m_forwardSpot->createUniform("spotLight.pointLight.base.color");
  m_forwardSpot->createUniform("spotLight.pointLight.base.intensity");

  m_forwardSpot->createUniform("spotLight.pointLight.attenuation.constant");
  m_forwardSpot->createUniform("spotLight.pointLight.attenuation.linear");
  m_forwardSpot->createUniform("spotLight.pointLight.attenuation.exponent");

  m_forwardSpot->createUniform("spotLight.pointLight.position");
  m_forwardSpot->createUniform("spotLight.pointLight.range");

  m_forwardSpot->createUniform("spotLight.cutoff");
  m_forwardSpot->createUniform("spotLight.direction");

  m_forwardSpot->createUniform("diffuseMap");
  m_forwardSpot->createUniform("normalMap");
  m_forwardSpot->createUniform("specularMap");

  m_forwardSpot->setUniform1i("diffuseMap", 0);
  m_forwardSpot->setUniform1i("normalMap", 1);
  m_forwardSpot->setUniform1i("specularMap", 2);
}
