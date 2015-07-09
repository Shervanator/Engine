//
//  Author: Shervin Aflatooni
//

#include "GLManager.h"

GLManager::GLManager(int width, int height)
{
  this->width = width;
  this->height = height;
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  glClearDepthf(1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glEnable(GL_CULL_FACE);

  glViewport(0, 0, this->width, this->height);

  createShaders();

  glGenBuffers(1, &lineBuffer);
}

GLManager::~GLManager(void)
{
  delete forwardAmbient;
  delete forwardDirectional;
  delete forwardPoint;
  delete forwardSpot;
  glDeleteBuffers(1, &lineBuffer);
}

void GLManager::setActiveCamera(Camera *camera)
{
  m_activeCamera = camera;
}

void GLManager::addDirectionalLight(DirectionalLight *light)
{
  m_directionalLights.push_back(light);
}

void GLManager::addPointLight(PointLight *light)
{
  m_pointLights.push_back(light);
}

void GLManager::addSpotLight(SpotLight *light)
{
  m_spotLights.push_back(light);
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
  simple->bind();

  simple->setUniformMatrix4f("World", glm::mat4());
  simple->setUniformMatrix4f("View", m_activeCamera->getViewMatrix());
  simple->setUniformMatrix4f("Proj", m_activeCamera->getProjectionMatrix());

  line.render(simple);
}

void GLManager::drawEntity(Entity *entity)
{
  simple->bind();

  // simple->setUniformMatrix4f("World", glm::mat4());
  simple->setUniformMatrix4f("View", m_activeCamera->getViewMatrix());
  simple->setUniformMatrix4f("Proj", m_activeCamera->getProjectionMatrix());

  glEnable(GL_BLEND);
  glBlendFunc(GL_ONE, GL_ONE);
  glDepthMask(GL_FALSE);
  glDepthFunc(GL_EQUAL);
  entity->renderAll(simple);
  glDepthFunc(GL_LESS);
  glDepthMask(GL_TRUE);
  glDisable(GL_BLEND);
}

void GLManager::renderScene(Entity *scene)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  forwardAmbient->setUniformMatrix4f("View", m_activeCamera->getViewMatrix());
  forwardAmbient->setUniformMatrix4f("Proj", m_activeCamera->getProjectionMatrix());

  scene->renderAll(forwardAmbient);

  glEnable(GL_BLEND);
  glBlendFunc(GL_ONE, GL_ONE);
  glDepthMask(GL_FALSE);
  glDepthFunc(GL_EQUAL);

  renderLights(m_directionalLights, forwardDirectional, scene);
  renderLights(m_pointLights, forwardPoint, scene);
  renderLights(m_spotLights, forwardSpot, scene);

  glDepthFunc(GL_LESS);
  glDepthMask(GL_TRUE);
  glDisable(GL_BLEND);
}

void GLManager::renderLights(std::vector<BaseLight *> &lights, Shader *shader, Entity *scene)
{
  shader->setUniformMatrix4f("View", m_activeCamera->getViewMatrix());
  shader->setUniformMatrix4f("Proj", m_activeCamera->getProjectionMatrix());
  shader->setUniformVec3f("eyePos", m_activeCamera->getParent()->getPosition().xyz());

  shader->setUniform1f("specularIntensity", 0.5);
  shader->setUniform1f("specularPower", 10);
  for (int i = 0; i < lights.size(); i++) {
    lights[i]->updateShader(shader);

    scene->renderAll(shader);
  }
}

void GLManager::createShaders(void)
{
  simple = new Shader("shaders/simple");
  simple->setAttribLocation("position", 0);
  simple->link();

  simple->createUniform("View");
  simple->createUniform("Proj");
  simple->createUniform("World");

  forwardAmbient = new Shader("shaders/forward-ambient");
  forwardAmbient->setAttribLocation("position", 0);
  forwardAmbient->setAttribLocation("texCoord", 1);
  forwardAmbient->link();

  forwardAmbient->createUniform("View");
  forwardAmbient->createUniform("Proj");
  forwardAmbient->createUniform("World");
  forwardAmbient->createUniform("ambientIntensity");

  forwardAmbient->createUniform("diffuseMap");

  forwardAmbient->setUniform1i("diffuseMap", 0);

  forwardAmbient->setUniformVec3f("ambientIntensity", glm::vec3(1, 1, 1));

  forwardDirectional = new Shader("shaders/forward-directional");
  forwardDirectional->setAttribLocation("position", 0);
  forwardDirectional->setAttribLocation("texCoord", 1);
  forwardDirectional->setAttribLocation("normal", 2);
  forwardDirectional->setAttribLocation("tangent", 3);
  forwardDirectional->link();

  forwardDirectional->createUniform("View");
  forwardDirectional->createUniform("Proj");
  forwardDirectional->createUniform("World");

  forwardDirectional->createUniform("eyePos");
  forwardDirectional->createUniform("specularIntensity");
  forwardDirectional->createUniform("specularPower");

  forwardDirectional->createUniform("directionalLight.base.color");
  forwardDirectional->createUniform("directionalLight.base.intensity");

  forwardDirectional->createUniform("directionalLight.direction");

  forwardDirectional->createUniform("diffuseMap");
  forwardDirectional->createUniform("normalMap");
  forwardDirectional->createUniform("specularMap");

  forwardDirectional->setUniform1i("diffuseMap", 0);
  forwardDirectional->setUniform1i("normalMap", 1);
  forwardDirectional->setUniform1i("specularMap", 2);

  forwardPoint = new Shader("shaders/forward-point");
  forwardPoint->setAttribLocation("position", 0);
  forwardPoint->setAttribLocation("texCoord", 1);
  forwardPoint->setAttribLocation("normal", 2);
  forwardPoint->setAttribLocation("tangent", 3);
  forwardPoint->link();

  forwardPoint->createUniform("View");
  forwardPoint->createUniform("Proj");
  forwardPoint->createUniform("World");

  forwardPoint->createUniform("eyePos");
  forwardPoint->createUniform("specularIntensity");
  forwardPoint->createUniform("specularPower");

  forwardPoint->createUniform("pointLight.base.color");
  forwardPoint->createUniform("pointLight.base.intensity");

  forwardPoint->createUniform("pointLight.attenuation.constant");
  forwardPoint->createUniform("pointLight.attenuation.linear");
  forwardPoint->createUniform("pointLight.attenuation.exponent");

  forwardPoint->createUniform("pointLight.position");
  forwardPoint->createUniform("pointLight.range");

  forwardPoint->createUniform("diffuseMap");
  forwardPoint->createUniform("normalMap");
  forwardPoint->createUniform("specularMap");

  forwardPoint->setUniform1i("diffuseMap", 0);
  forwardPoint->setUniform1i("normalMap", 1);
  forwardPoint->setUniform1i("specularMap", 2);

  forwardSpot = new Shader("shaders/forward-spot");
  forwardSpot->setAttribLocation("position", 0);
  forwardSpot->setAttribLocation("texCoord", 1);
  forwardSpot->setAttribLocation("normal", 2);
  forwardSpot->setAttribLocation("tangent", 3);
  forwardSpot->link();

  forwardSpot->createUniform("View");
  forwardSpot->createUniform("Proj");
  forwardSpot->createUniform("World");

  forwardSpot->createUniform("eyePos");
  forwardSpot->createUniform("specularIntensity");
  forwardSpot->createUniform("specularPower");

  forwardSpot->createUniform("spotLight.pointLight.base.color");
  forwardSpot->createUniform("spotLight.pointLight.base.intensity");

  forwardSpot->createUniform("spotLight.pointLight.attenuation.constant");
  forwardSpot->createUniform("spotLight.pointLight.attenuation.linear");
  forwardSpot->createUniform("spotLight.pointLight.attenuation.exponent");

  forwardSpot->createUniform("spotLight.pointLight.position");
  forwardSpot->createUniform("spotLight.pointLight.range");

  forwardSpot->createUniform("spotLight.cutoff");
  forwardSpot->createUniform("spotLight.direction");

  forwardSpot->createUniform("diffuseMap");
  forwardSpot->createUniform("normalMap");
  forwardSpot->createUniform("specularMap");

  forwardSpot->setUniform1i("diffuseMap", 0);
  forwardSpot->setUniform1i("normalMap", 1);
  forwardSpot->setUniform1i("specularMap", 2);
}
