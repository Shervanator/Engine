#include "MediaLoader.h"
#include "Material.h"
#include "Texture.h"
#include "Logger.h"
#include "components/MeshRenderer.h"
#include "Plane.h"

MediaLoader::MediaLoader(const std::string file)
{
  initEntity(new Texture(Asset(file)));
}

MediaLoader::MediaLoader(Texture *texture)
{
  initEntity(texture);
}

MediaLoader::MediaLoader(Video *video)
{
  initEntity(texture);
}

MediaLoader::~MediaLoader(void)
{
}

void MediaLoader::initEntity(Texture *texture)
{
  m_entity = new Entity();
  m_entity->addComponent(new MeshRenderer((new Plane())->getMesh(), new Material(texture)));

  float aR = texture->getTextureData()->getWidth() / (texture->getTextureData()->getHeight() * 1.0f);
  m_entity->getTransform().setScale(glm::vec3(aR, 1, 1));
}

Entity *MediaLoader::getEntity(void)
{
  return m_entity;
}
