//
//  Author: Shervin Aflatooni
//

#include "CustomIOSystem.h"
#include "MeshLoader.h"
#include "Mesh.h"
#include "components/MeshRenderer.h"
#include "Material.h"
#include "Texture.h"

#include "Logger.h"

#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

MeshLoader::MeshLoader(const std::string file)
{
  m_fileName = file;

  Assimp::Importer importer;
  importer.SetIOHandler(new CustomIOSystem());

  log_info("Loading mesh: %s", file.c_str());

  const aiScene* scene = importer.ReadFile(file,
                                           aiProcess_Triangulate |
                                           aiProcess_GenSmoothNormals |
                                           aiProcess_FlipUVs |
                                           aiProcess_CalcTangentSpace);

  if(!scene) {
    log_err("Failed to load mesh: %s", file.c_str());
  } else {
    loadScene(scene);
  }

}

MeshLoader::~MeshLoader(void)
{
}

std::shared_ptr<Entity> MeshLoader::getEntity(void) const
{
  return m_entity;
}

void MeshLoader::loadScene(const aiScene* scene)
{
  m_entity = std::make_shared<Entity>();

  for (int i = 0; i < scene->mNumMeshes; i++) {
    const aiMesh* model = scene->mMeshes[i];

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    const aiVector3D aiZeroVector(0.0f, 0.0f, 0.0f);
    for(unsigned int i = 0; i < model->mNumVertices; i++)
    {
      const aiVector3D* pPos = &(model->mVertices[i]);
      const aiVector3D* pNormal = &(model->mNormals[i]);
      const aiVector3D* pTexCoord = model->HasTextureCoords(0) ? &(model->mTextureCoords[0][i]) : &aiZeroVector;
      const aiVector3D* pTangent = model->HasTangentsAndBitangents() ? &(model->mTangents[i]) : &aiZeroVector;

      Vertex vert(glm::vec3(pPos->x, pPos->y, pPos->z),
                  glm::vec2(pTexCoord->x, pTexCoord->y),
                  glm::vec3(pNormal->x, pNormal->y, pNormal->z),
                  glm::vec3(pTangent->x, pTangent->y, pTangent->z));

      vertices.push_back(vert);
    }

    for(unsigned int i = 0; i < model->mNumFaces; i++)
    {
      const aiFace& face = model->mFaces[i];
      indices.push_back(face.mIndices[0]);
      indices.push_back(face.mIndices[1]);
      indices.push_back(face.mIndices[2]);
    }

    const aiMaterial* pMaterial = scene->mMaterials[model->mMaterialIndex];
    log_info("tex num: %i", model->mMaterialIndex);

    std::shared_ptr<Texture> diffuseMap;
    std::shared_ptr<Texture> normalMap;
    std::shared_ptr<Texture> specularMap;

    aiString Path;

    if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0
        && pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
      diffuseMap = std::make_shared<Texture>(Asset(Path.data));
    } else {
      diffuseMap = std::make_shared<Texture>(Asset("default_normal.jpg"));
    }

    if (pMaterial->GetTextureCount(aiTextureType_HEIGHT) > 0
        && pMaterial->GetTexture(aiTextureType_HEIGHT, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
      normalMap = std::make_shared<Texture>(Asset(Path.data));
    } else {
      normalMap = std::make_shared<Texture>(Asset("default_normal.jpg"));
    }

    if (pMaterial->GetTextureCount(aiTextureType_SPECULAR) > 0
        && pMaterial->GetTexture(aiTextureType_SPECULAR, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
      specularMap = std::make_shared<Texture>(Asset(Path.data));
    } else {
      specularMap = std::make_shared<Texture>(Asset("default_specular.jpg"));
    }

    m_entity->addComponent<MeshRenderer>(
        std::make_shared<Mesh>(m_fileName + std::string(model->mName.C_Str()), &vertices[0], vertices.size(), &indices[0], indices.size()),
        std::make_shared<Material>(diffuseMap, normalMap, specularMap)
    );
  }
}
