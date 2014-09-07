#include "GLManager.h"

#include "FreeLook.h"
#include "FreeMove.h"

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
}

GLManager::~GLManager(void)
{
  delete forwardAmbient;
  delete forwardDirectional;
  delete forwardPoint;
  delete forwardSpot;
}

void GLManager::setActiveCamera(Camera *camera)
{
  m_activeCamera = camera;
}

void GLManager::addLight(BaseLight *light)
{
  m_lights.push_back(light);
}

void GLManager::renderScene(Entity *scene)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  forwardAmbient->setUniformMatrix4f("ViewProj", m_activeCamera->getViewProjection());

  scene->renderAll(forwardAmbient);

  glEnable(GL_BLEND);
  glBlendFunc(GL_ONE, GL_ONE);
  glDepthMask(GL_FALSE);
  glDepthFunc(GL_EQUAL);

  forwardSpot->setUniformMatrix4f("ViewProj", m_activeCamera->getViewProjection());
  forwardSpot->setUniformVec3f("eyePos", m_activeCamera->getParent()->getPosition());

  forwardSpot->setUniform1f("specularIntensity", 1);
  forwardSpot->setUniform1f("specularPower", 10);
  for (int i = 0; i < m_lights.size(); i++) {
    m_lights[i]->updateShader(forwardSpot);

    scene->renderAll(forwardSpot);
  }

  glDepthFunc(GL_LESS);
  glDepthMask(GL_TRUE);
  glDisable(GL_BLEND);
}

void GLManager::createShaders(void)
{
  forwardAmbient = new Shader("forward-ambient");
  forwardAmbient->setAttribLocation("position", 0);
  forwardAmbient->setAttribLocation("texCoord", 1);
  forwardAmbient->link();

  forwardAmbient->createUniform("ViewProj");
  forwardAmbient->createUniform("World");
  forwardAmbient->createUniform("ambientIntensity");

  forwardAmbient->createUniform("diffuseMap");

  forwardAmbient->setUniform1i("diffuseMap", 0);

  forwardAmbient->setUniformVec3f("ambientIntensity", glm::vec3(0.2f, 0.2f, 0.2f));

  forwardDirectional = new Shader("forward-directional");
  forwardDirectional->setAttribLocation("position", 0);
  forwardDirectional->setAttribLocation("texCoord", 1);
  forwardDirectional->setAttribLocation("normal", 2);
  forwardDirectional->link();

  forwardDirectional->createUniform("ViewProj");
  forwardDirectional->createUniform("World");

  forwardDirectional->createUniform("eyePos");
  forwardDirectional->createUniform("specularIntensity");
  forwardDirectional->createUniform("specularPower");

  forwardDirectional->createUniform("directionalLight.base.color");
  forwardDirectional->createUniform("directionalLight.base.intensity");

  forwardDirectional->createUniform("directionalLight.direction");

  forwardDirectional->createUniform("diffuseMap");

  forwardDirectional->setUniform1i("diffuseMap", 0);

  forwardPoint = new Shader("forward-point");
  forwardPoint->setAttribLocation("position", 0);
  forwardPoint->setAttribLocation("texCoord", 1);
  forwardPoint->setAttribLocation("normal", 2);
  forwardPoint->link();

  forwardPoint->createUniform("ViewProj");
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

  forwardPoint->setUniform1i("diffuseMap", 0);

  forwardSpot = new Shader("forward-spot");
  forwardSpot->setAttribLocation("position", 0);
  forwardSpot->setAttribLocation("texCoord", 1);
  forwardSpot->setAttribLocation("normal", 2);
  forwardSpot->link();

  forwardSpot->createUniform("ViewProj");
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

  forwardSpot->setUniform1i("diffuseMap", 0);
}
