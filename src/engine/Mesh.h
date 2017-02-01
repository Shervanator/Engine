//
//  Author: Shervin Aflatooni
//

#pragma once

#include "Vertex.h"
#include "MeshData.h"

#include <string>
#include <memory>

class Mesh
{
public:
  Mesh(std::string identifier, Vertex vertices[], int vertSize, unsigned int indices[], int indexSize);
  virtual ~Mesh(void);

  void render(void) const;

private:
  std::shared_ptr<MeshData> m_meshData;
};
