#include "SimpleRenderer.h"

SimpleRenderer::SimpleRenderer()
{
  createShaders();
}

SimpleRenderer::~SimpleRenderer()
{
}

void SimpleRenderer::render(const Entity &scene, std::shared_ptr<Camera> activeCamera, const std::vector<std::shared_ptr<PointLight>> &pointLights, const std::vector<std::shared_ptr<DirectionalLight>> &directionalLights, const std::vector<std::shared_ptr<SpotLight>> &spotLights) const
{
  m_simple->bind();

  m_simple->setUniformMatrix4f("World", glm::mat4());
  m_simple->setUniformMatrix4f("View", activeCamera->getViewMatrix());
  m_simple->setUniformMatrix4f("Proj", activeCamera->getProjectionMatrix());

  scene.renderAll(m_simple.get());
}

void SimpleRenderer::renderLine(const Line &line, std::shared_ptr<Camera> activeCamera) const
{
  m_simple->bind();

  m_simple->setUniformMatrix4f("World", glm::mat4());
  m_simple->setUniformMatrix4f("View", activeCamera->getViewMatrix());
  m_simple->setUniformMatrix4f("Proj", activeCamera->getProjectionMatrix());

  line.render(m_simple.get());
}

void SimpleRenderer::createShaders()
{
  m_simple = std::make_unique<Shader>("shaders/simple");
  m_simple->setAttribLocation("position", 0);
  m_simple->link();

  m_simple->createUniform("View");
  m_simple->createUniform("Proj");
  m_simple->createUniform("World");
}
