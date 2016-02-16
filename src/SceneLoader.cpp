//
//  Author: Shervin Aflatooni
//

#include "CustomIOSystem.h"
#include "SceneLoader.h"
#include "Mesh.h"
#include "components/MeshRenderer.h"
#include "Material.h"
#include "Texture.h"

#include "Logger.h"

#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

SceneLoader::SceneLoader(const std::string file)
{
  m_fileName = file;

  Assimp::Importer importer;
  importer.SetIOHandler(new CustomIOSystem());

  log_info("Loading scene: %s", file.c_str());

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

SceneLoader::~SceneLoader(void)
{
}

Entity *SceneLoader::getEntity(void)
{
  return m_entity;
}

Camera *SceneLoader::getCamera(void)
{
  return m_camera;
}

Mesh* SceneLoader::loadMesh(const aiMesh* mesh)
{
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;

  const aiVector3D aiZeroVector(0.0f, 0.0f, 0.0f);
  for(unsigned int i = 0; i < mesh->mNumVertices; i++)
  {
    const aiVector3D* pPos = &(mesh->mVertices[i]);
    const aiVector3D* pNormal = &(mesh->mNormals[i]);
    const aiVector3D* pTexCoord = mesh->HasTextureCoords(0) ? &(mesh->mTextureCoords[0][i]) : &aiZeroVector;
    const aiVector3D* pTangent = mesh->HasTangentsAndBitangents() ? &(mesh->mTangents[i]) : &aiZeroVector;

    Vertex vert(glm::vec3(pPos->x, pPos->y, pPos->z),
                glm::vec2(pTexCoord->x, pTexCoord->y),
                glm::vec3(pNormal->x, pNormal->y, pNormal->z),
                glm::vec3(pTangent->x, pTangent->y, pTangent->z));

    vertices.push_back(vert);
  }

  for(unsigned int i = 0; i < mesh->mNumFaces; i++)
  {
    const aiFace& face = mesh->mFaces[i];
    indices.push_back(face.mIndices[0]);
    indices.push_back(face.mIndices[1]);
    indices.push_back(face.mIndices[2]);
  }

  return new Mesh(m_fileName + std::string(mesh->mName.C_Str()), &vertices[0], vertices.size(), &indices[0], indices.size());
}

Material* SceneLoader::loadMaterial(const aiMaterial* material)
{
  Texture *diffuseMap = NULL;
  Texture *normalMap = NULL;
  Texture *specularMap = NULL;

  aiString Path;

  if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0
      && material->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
    diffuseMap = new Texture(Asset(Path.data));
  } else {
    diffuseMap = new Texture(Asset("default_normal.jpg"));
  }

  if (material->GetTextureCount(aiTextureType_HEIGHT) > 0
      && material->GetTexture(aiTextureType_HEIGHT, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
    normalMap = new Texture(Asset(Path.data));
  } else {
    normalMap = new Texture(Asset("default_normal.jpg"));
  }

  if (material->GetTextureCount(aiTextureType_SPECULAR) > 0
      && material->GetTexture(aiTextureType_SPECULAR, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
    specularMap = new Texture(Asset(Path.data));
  } else {
    specularMap = new Texture(Asset("default_specular.jpg"));
  }

  return new Material(diffuseMap, normalMap, specularMap);
}

Entity* SceneLoader::loadGraph(aiNode* node, Entity* parentEntity, const aiScene* scene)
{
  Entity *entity = new Entity();

  std::map<std::string, aiNodeAnim *>::const_iterator it = m_nodeAnimation.find(std::string(node->mName.C_Str()));
  if(it != m_nodeAnimation.end()) {
    log_info("Found animation: %i", it->second->mNumPositionKeys);

    // entity->getTransform().setPosition(glm::vec3(it->second->mPositionKeys[0].mValue[0], it->second->mPositionKeys[0].mValue[1], it->second->mPositionKeys[0].mValue[2]));
  }

  for (int i = 0; i < node->mNumChildren; i++) {
    aiNode* childNode = node->mChildren[i];

    for (int j = 0; j < childNode->mNumMeshes; j++) {
      const aiMesh* mesh = scene->mMeshes[childNode->mMeshes[j]];
      const aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
      entity->addComponent(
        new MeshRenderer(
          loadMesh(mesh),
          loadMaterial(material)
      ));
    }
    parentEntity->addChild(loadGraph(childNode, entity, scene));
  }

  return entity;
}

void SceneLoader::loadScene(const aiScene* scene)
{
  if (scene->HasAnimations()) {
    for(int i = 0; i < scene->mNumAnimations; i++) {
      aiAnimation *anim = scene->mAnimations[i];
      for (int j = 0; j < anim->mNumChannels; j++) {
        aiNodeAnim *nodeAnim = anim->mChannels[j];
        m_nodeAnimation[std::string(nodeAnim->mNodeName.C_Str())] = nodeAnim;
      }
    }
  }

  m_entity = new Entity();
  loadGraph(scene->mRootNode, m_entity, scene);

  if (scene->HasCameras()) {
    for (int i = 0; i < scene->mNumCameras; i++) {
      const aiCamera* camera = scene->mCameras[i];

      m_entity->addComponent(m_camera = new Camera(camera->mHorizontalFOV, camera->mAspect, camera->mClipPlaneNear, camera->mClipPlaneFar));
    }
  }
}
