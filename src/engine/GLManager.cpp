//
//  Author: Shervin Aflatooni
//

#include "GLManager.h"
#include "Logger.h"

#include <algorithm>

GLManager::GLManager(std::unique_ptr<Renderer> renderer, const glm::vec2 &windowSize)
{
  m_renderer = std::move(renderer);
  m_simpleRenderer = std::make_unique<SimpleRenderer>();

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  glClearDepthf(1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glEnable(GL_CULL_FACE);

  setDrawSize(windowSize);

  glGenBuffers(1, &lineBuffer);
}

GLManager::~GLManager(void)
{
  glDeleteBuffers(1, &lineBuffer);
}

void GLManager::setDrawSize(const glm::vec2 &size)
{
  this->width = size.x;
  this->height = size.y;

  glViewport(0, 0, this->width, this->height);
}

void GLManager::bindRenderTarget(void) const
{
  glBindTexture(GL_TEXTURE_2D, 0);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glViewport(0, 0, this->width, this->height);
}

void GLManager::setActiveCamera(std::shared_ptr<Camera> camera)
{
  m_activeCamera = camera;
}

void GLManager::addDirectionalLight(std::shared_ptr<DirectionalLight> light)
{
  m_directionalLights.push_back(light);
}

void GLManager::removeDirectionalLight(std::shared_ptr<DirectionalLight> light)
{
  m_directionalLights.erase(std::remove(m_directionalLights.begin(), m_directionalLights.end(), light), m_directionalLights.end());
}

void GLManager::addPointLight(std::shared_ptr<PointLight> light)
{
  m_pointLights.push_back(light);
}

void GLManager::removePointLight(std::shared_ptr<PointLight> light)
{
  m_pointLights.erase(std::remove(m_pointLights.begin(), m_pointLights.end(), light), m_pointLights.end());
}

void GLManager::addSpotLight(std::shared_ptr<SpotLight> light)
{
  m_spotLights.push_back(light);
}

void GLManager::removeSpotLight(std::shared_ptr<SpotLight> light)
{
  m_spotLights.erase(std::remove(m_spotLights.begin(), m_spotLights.end(), light), m_spotLights.end());
}

glm::mat4 GLManager::getViewMatrix(void)
{
  return m_activeCamera->getViewMatrix();
}

glm::mat4 GLManager::getProjectionMatrix(void)
{
  return m_activeCamera->getProjectionMatrix();
}

void GLManager::drawLine(Line line)
{
  m_simpleRenderer->renderLine(line, m_activeCamera);
}

void GLManager::drawEntity(Entity *entity)
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_ONE, GL_ONE);
  glDepthMask(GL_FALSE);
  glDepthFunc(GL_EQUAL);

  m_simpleRenderer->render(*entity, m_activeCamera, m_pointLights, m_directionalLights, m_spotLights);

  glDepthFunc(GL_LESS);
  glDepthMask(GL_TRUE);
  glDisable(GL_BLEND);
}

void GLManager::renderScene(Entity *scene)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  m_renderer->render(*scene, m_activeCamera, m_pointLights, m_directionalLights, m_spotLights);
}
