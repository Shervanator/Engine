//
//  Author: Shervin Aflatooni
//

#include "Mesh.h"

#include <map>

std::map<std::string, MeshData *> m_meshCache;

Mesh::Mesh(std::string identifier, Vertex vertices[], int vertSize, unsigned int indices[], int indexSize)
{
  std::map<std::string, MeshData *>::const_iterator it = m_meshCache.find(identifier);

  if(it != m_meshCache.end()) {
    m_meshData = it->second;
  } else {
    m_meshData = m_meshCache[identifier] = new MeshData(vertices, vertSize, indices, indexSize);
  }

  m_meshData->incrementReference();
}

Mesh::~Mesh(void)
{
  m_meshData->decrementReference();
}

void Mesh::render(void)
{
  m_meshData->render();
}
