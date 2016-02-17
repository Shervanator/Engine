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

#include "components/FreeMove.h"
#include "components/FreeLook.h"
#include "components/Animation.h"

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

Entity* SceneLoader::loadGraph(aiNode* node, const aiScene* scene)
{
  Entity *entity = new Entity();

  entity->name = std::string(node->mName.C_Str());

  aiVector3D scale;
  aiQuaternion rotation;
  aiVector3D position;
  node->mTransformation.Decompose(scale, rotation, position);
  entity->getTransform().setPosition(glm::vec3(position.x, position.y, position.z));
  entity->getTransform().setRotation(glm::quat(rotation.w, rotation.x, rotation.y, rotation.z));
  entity->getTransform().setScale(glm::vec3(scale.x, scale.y, scale.z));

  std::map<std::string, aiNodeAnim *>::const_iterator it = m_nodeAnimation.find(std::string(node->mName.C_Str()));
  if(it != m_nodeAnimation.end()) {
    Animation *animation = new Animation();
    entity->addComponent(animation);

    for (int i = 0; i < it->second->mNumPositionKeys; i++) {
      animation->addPosition(glm::vec3(it->second->mPositionKeys[i].mValue.x, it->second->mPositionKeys[i].mValue.y, it->second->mPositionKeys[i].mValue.z));
      animation->addRotation(glm::quat(it->second->mRotationKeys[i].mValue.w, it->second->mRotationKeys[i].mValue.x, it->second->mRotationKeys[i].mValue.y, it->second->mRotationKeys[i].mValue.z));
      animation->addScale(glm::vec3(it->second->mScalingKeys[i].mValue.x, it->second->mScalingKeys[i].mValue.y, it->second->mScalingKeys[i].mValue.z));
    }
  }

  std::map<std::string, aiCamera *>::const_iterator it2 = m_nodeCamera.find(std::string(node->mName.C_Str()));
  if(it2 != m_nodeCamera.end()) {
    entity->addComponent(new FreeMove());
    entity->addComponent(new FreeLook());

    entity->addComponent(m_camera = new Camera(it2->second->mHorizontalFOV, it2->second->mAspect, it2->second->mClipPlaneNear, it2->second->mClipPlaneFar));
  }

  for (int j = 0; j < node->mNumMeshes; j++) {
    const aiMesh* mesh = scene->mMeshes[node->mMeshes[j]];
    const aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    entity->addComponent(
      new MeshRenderer(
        loadMesh(mesh),
        loadMaterial(material)
    ));
  }

  for (int i = 0; i < node->mNumChildren; i++) {
    aiNode* childNode = node->mChildren[i];
    entity->addChild(loadGraph(childNode, scene));
  }

  return entity;
}

void debugEntities(Entity *entity)
{
  entity->calculateWorldMatrix();

  log_info("_____________________________________________");
  log_info("Entity: %s", entity->name.c_str());
  log_info("Position: %f %f %f", entity->getTransform().getPosition().x, entity->getTransform().getPosition().y, entity->getTransform().getPosition().z);
  log_info("PositionWorld: %f %f %f", entity->getPosition().x, entity->getPosition().y, entity->getPosition().z);
  glm::vec3 lol = glm::eulerAngles(glm::quat(entity->getTransform().getRotation().w, entity->getTransform().getRotation().x, entity->getTransform().getRotation().y, entity->getTransform().getRotation().z));
  log_info("Rotation (Degrees): %f %f %f", glm::degrees(lol.x), glm::degrees(lol.y), glm::degrees(lol.z));
  log_info("Rotation: %f %f %f %f",  entity->getTransform().getRotation().w, entity->getTransform().getRotation().x, entity->getTransform().getRotation().y, entity->getTransform().getRotation().z);
  log_info("Scale: %f %f %f",  entity->getTransform().getScale().x, entity->getTransform().getScale().y, entity->getTransform().getScale().z);

  if (entity->getParent() != NULL) {
    log_info("Parent: %s", entity->getParent()->name.c_str());
  }
  log_info("_____________________________________________");

  std::vector<Entity*> entities = *entity->getChildren();
  for (int i = 0; i < entities.size(); i++)
    debugEntities(entities[i]);
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

  if (scene->HasCameras()) {
    for (int i = 0; i < scene->mNumCameras; i++) {
      aiCamera* camera = scene->mCameras[i];
      m_nodeCamera[std::string(camera->mName.C_Str())] = camera;
    }
  }

  m_entity = loadGraph(scene->mRootNode, scene);

  debugEntities(m_entity);
}
