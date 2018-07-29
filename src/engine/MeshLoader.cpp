//
//  Author: Shervin Aflatooni
//

#include "CustomIOSystem.h"
#include "MeshLoader.h"
#include "components/MeshRenderer.h"

#include "Logger.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

// TODO: need to come back and refactor this, make it load on a seperate thread.
std::map<std::string, std::vector<MeshRendererData>> MeshLoader::sceneMeshRendererDataCache;

MeshLoader::MeshLoader(const std::string file)
{
  m_fileName = file;

  if (MeshLoader::sceneMeshRendererDataCache[m_fileName].size() > 0)
  {
    m_entity = std::make_shared<Entity>();
    for (auto meshRenderData : MeshLoader::sceneMeshRendererDataCache[m_fileName])
    {
      m_entity->addComponent<MeshRenderer>(meshRenderData.mesh, meshRenderData.material);
    }
  }
  else
  {
    Assimp::Importer importer;
    importer.SetIOHandler(new CustomIOSystem());

    const aiScene *scene = importer.ReadFile(file,
                                             aiProcess_Triangulate |
                                                 aiProcess_GenSmoothNormals |
                                                 aiProcess_FlipUVs |
                                                 aiProcess_CalcTangentSpace); //*/

    if (!scene)
    {
      log_err("Failed to load mesh: %s", file.c_str());
    }
    else
      loadScene(scene);
  }
}

std::shared_ptr<Entity> MeshLoader::getEntity(void) const
{
  return m_entity;
}

void MeshLoader::loadScene(const aiScene *scene)
{
  m_entity = std::make_shared<Entity>();

  for (int i = 0; i < scene->mNumMeshes; i++)
  {
    const aiMesh *model = scene->mMeshes[i];

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    const aiVector3D aiZeroVector(0.0f, 0.0f, 0.0f);
    for (unsigned int i = 0; i < model->mNumVertices; i++)
    {
      const aiVector3D *pPos = &(model->mVertices[i]);
      const aiVector3D *pNormal = &(model->mNormals[i]);
      const aiVector3D *pTexCoord = model->HasTextureCoords(0) ? &(model->mTextureCoords[0][i]) : &aiZeroVector;
      const aiVector3D *pTangent = model->HasTangentsAndBitangents() ? &(model->mTangents[i]) : &aiZeroVector;

      Vertex vert(glm::vec3(pPos->x, pPos->y, pPos->z),
                  glm::vec2(pTexCoord->x, pTexCoord->y),
                  glm::vec3(pNormal->x, pNormal->y, pNormal->z),
                  glm::vec3(pTangent->x, pTangent->y, pTangent->z));

      vertices.push_back(vert);
    }

    for (unsigned int i = 0; i < model->mNumFaces; i++)
    {
      const aiFace &face = model->mFaces[i];
      indices.push_back(face.mIndices[0]);
      indices.push_back(face.mIndices[1]);
      indices.push_back(face.mIndices[2]);
    }

    const aiMaterial *pMaterial = scene->mMaterials[model->mMaterialIndex];
    log_info("tex num: %i", model->mMaterialIndex);

    std::shared_ptr<Texture> diffuseMap;
    std::shared_ptr<Texture> normalMap;
    std::shared_ptr<Texture> specularMap;

    aiString Path;

    if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0 && pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
    {
      diffuseMap = std::make_shared<Texture>(Asset(Path.data));
    }
    else
    {
      diffuseMap = std::make_shared<Texture>(Asset("default_normal.jpg"));
    }

    if (pMaterial->GetTextureCount(aiTextureType_HEIGHT) > 0 && pMaterial->GetTexture(aiTextureType_HEIGHT, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
    {
      normalMap = std::make_shared<Texture>(Asset(Path.data));
    }
    else
    {
      normalMap = std::make_shared<Texture>(Asset("default_normal.jpg"));
    }

    if (pMaterial->GetTextureCount(aiTextureType_SPECULAR) > 0 && pMaterial->GetTexture(aiTextureType_SPECULAR, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
    {
      specularMap = std::make_shared<Texture>(Asset(Path.data));
    }
    else
    {
      specularMap = std::make_shared<Texture>(Asset("default_specular.jpg"));
    }

    MeshRendererData meshRenderData;
    meshRenderData.mesh = std::make_shared<Mesh>(m_fileName + std::string(model->mName.C_Str()), &vertices[0], vertices.size(), &indices[0], indices.size());
    meshRenderData.material = std::make_shared<Material>(diffuseMap, normalMap, specularMap);

    MeshLoader::sceneMeshRendererDataCache[m_fileName].push_back(meshRenderData);
    m_entity->addComponent<MeshRenderer>(meshRenderData.mesh, meshRenderData.material);
  }
}

/////Added by Majid Anjidani/////////////////////////////////////
// TODO: need to come back and refactor this, make it load on a seperate thread.

SkeletalAnimationModelLoader::SkeletalAnimationModelLoader(const std::string file, glm::quat rotation, float scal) : transformation()
{
  //if(rotation){
  aiVector3D scale(scal);
  aiVector3D position(0.0);
  const aiQuaternion rotat(rotation.w, rotation.x, rotation.y, rotation.z);
  transformation = aiMatrix4x4Compose(scale, rotat, position);
  //}
  ///////////////////////////////////*/
  m_fileName = file;
  Assimp::Importer importer;
  importer.SetIOHandler(new CustomIOSystem());

  const aiScene *scene = importer.ReadFile(file,
                                           aiProcess_Triangulate |
                                               aiProcess_GenSmoothNormals |
                                               aiProcess_FlipUVs |
                                               aiProcess_CalcTangentSpace); //*/

  if (!scene)
  {
    log_err("Failed to load mesh: %s", file.c_str());
  }
  else
  {
    MeshLoader::loadScene(scene);
    read_Meshes_Channels_Bones(scene);
  }
}

void SkeletalAnimationModelLoader::createFrame(unsigned int animationId, double time, bool loop)
{
  if (animationId < animations.size())
  {
    for (auto &channel : animations[animationId].channels)
    {
      aiVector3D scale = animations[animationId].interpolate(channel.scales, time, true);
      aiQuaternion rotation = animations[animationId].interpolate(channel.rotations, time, true);
      aiVector3D position = animations[animationId].interpolate(channel.positions, time, true);
      bones[channel.boneId].transformation = aiMatrix4x4Compose(scale, rotation, position);
    }
  }
}

SkeletalAnimationModelLoader::MeshFrame SkeletalAnimationModelLoader::getMeshFrame(const MeshExtended &mesh) const
{
  MeshFrame meshFrame(mesh);

  //Calculate new frame vertices and normals
  for (unsigned int cb = 0; cb < mesh.boneWeights.size(); cb++)
  {
    const auto &boneWeights = mesh.boneWeights[cb];

    aiMatrix4x4 transformat = transformation;
    const std::function<void(unsigned int)> calculateBoneTransformation = [&](unsigned int boneId) {
      if (bones[boneId].hasParentBoneId)
      {
        calculateBoneTransformation(bones[boneId].parentBoneId);
      }
      transformat *= bones[boneId].transformation;
    };
    calculateBoneTransformation(boneWeights.boneId);
    transformat *= boneWeights.offsetMatrix;

    for (auto &weight : boneWeights.weights)
    {
      meshFrame.vertices[weight.mVertexId] += weight.mWeight * (transformat * mesh.vertices[weight.mVertexId]);
      meshFrame.normals[weight.mVertexId] += weight.mWeight * (aiMatrix3x3(transformat) * mesh.normals[weight.mVertexId]);
      meshFrame.tangents[weight.mVertexId] += weight.mWeight * (aiMatrix3x3(transformat) * mesh.tangents[weight.mVertexId]);
    }
  }

  return meshFrame;
}
/*void SkeletalAnimationModelLoader::loadscene()//(unsigned int animationId, double time)
{
	createFrame(0, 0);
	//if (m_entity) m_entity->delComponents<MeshRenderer>();
	//else m_entity = std::make_shared<Entity>();
	m_entity = std::make_shared<Entity>();

	for (int k = 0; k < meshes.size(); k++)
	{
		MeshFrame meshFrame = getMeshFrame(meshes[k]);

		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;

		const aiVector3D aiZeroVector(0.0f, 0.0f, 0.0f);
		for (unsigned int i = 0; i < meshFrame.vertices.size(); i++)
		{
			const aiVector3D* pPos = &(meshFrame.vertices[i]);
			const aiVector3D* pNormal = &(meshes[k].normals[i]);
			const aiVector2D* pTexCoord = &(meshes[k].textureCoords[i]);
			const aiVector3D* pTangent = &(meshFrame.tangents[i]);

			Vertex vert(glm::vec3(pPos->x, pPos->y, pPos->z),
				glm::vec2(pTexCoord->x, pTexCoord->y),
				glm::vec3(pNormal->x, pNormal->y, pNormal->z),
				glm::vec3(pTangent->x, pTangent->y, pTangent->z));

			vertices.push_back(vert);
		}
		for (unsigned int i = 0; i < meshes[k].faces.size(); i++)
		{
			indices.push_back(meshes[k].faces[i].mIndices[0]);
			indices.push_back(meshes[k].faces[i].mIndices[1]);
			indices.push_back(meshes[k].faces[i].mIndices[2]);
		}

		MeshRendererData meshRenderData;
		meshRenderData.mesh = std::make_shared<Mesh>(m_fileName + meshes[k].name, &vertices[0], vertices.size(), &indices[0], indices.size());
		meshRenderData.material = Materials[k];

		MeshLoader::sceneMeshRendererDataCache[m_fileName].push_back(meshRenderData);
		m_entity->addComponent<MeshRenderer>(meshRenderData.mesh, meshRenderData.material);
		//log_info("Majid: %i", 225);
	}
}//*/
void SkeletalAnimationModelLoader::loadNewFrame(unsigned int animationId, double time)
{
  createFrame(animationId, time);

  for (int k = 0; k < meshes.size(); k++)
  {
    MeshFrame meshFrame = getMeshFrame(meshes[k]);

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    const aiVector3D aiZeroVector(0.0f, 0.0f, 0.0f);
    for (unsigned int i = 0; i < meshFrame.vertices.size(); i++)
    {
      const aiVector3D *pPos = &(meshFrame.vertices[i]);
      const aiVector3D *pNormal = &(meshes[k].normals[i]);
      const aiVector2D *pTexCoord = &(meshes[k].textureCoords[i]);
      const aiVector3D *pTangent = &(meshFrame.tangents[i]);

      Vertex vert(glm::vec3(pPos->x, pPos->y, pPos->z),
                  glm::vec2(pTexCoord->x, pTexCoord->y),
                  glm::vec3(pNormal->x, pNormal->y, pNormal->z),
                  glm::vec3(pTangent->x, pTangent->y, pTangent->z));

      vertices.push_back(vert);
    }
    for (unsigned int i = 0; i < meshes[k].faces.size(); i++)
    {
      indices.push_back(meshes[k].faces[i].mIndices[0]);
      indices.push_back(meshes[k].faces[i].mIndices[1]);
      indices.push_back(meshes[k].faces[i].mIndices[2]);
    }

    MeshLoader::sceneMeshRendererDataCache[m_fileName][k].mesh->reasign(m_fileName + meshes[k].name, &vertices[0], vertices.size(), &indices[0], indices.size());
    //log_info("Majid: %i", 225);
  }
}
/*void SkeletalAnimationModelLoader::loadScene(unsigned int animationId, double time)
{
	createFrame(animationId, time);
	m_entity = std::make_shared<Entity>();

	for (int k = 0; k < meshes.size(); k++) {
		MeshFrame meshFrame = getMeshFrame(meshes[k]);

		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;

		const aiVector3D aiZeroVector(0.0f, 0.0f, 0.0f);
		for (unsigned int i = 0; i < meshFrame.vertices.size(); i++)
		{
			const aiVector3D* pPos = &(meshFrame.vertices[i]);
			const aiVector3D* pNormal = &(meshes[k].normals[i]);
			const aiVector2D* pTexCoord = &(meshes[k].textureCoords[i]);
			const aiVector3D* pTangent = &(meshFrame.tangents[i]);

			Vertex vert(glm::vec3(pPos->x, pPos->y, pPos->z),
				glm::vec2(pTexCoord->x, pTexCoord->y),
				glm::vec3(pNormal->x, pNormal->y, pNormal->z),
				glm::vec3(pTangent->x, pTangent->y, pTangent->z));

			vertices.push_back(vert);
		}
		for (unsigned int i = 0; i < meshes[k].faces.size(); i++)
		{
			indices.push_back(meshes[k].faces[i].mIndices[0]);
			indices.push_back(meshes[k].faces[i].mIndices[1]);
			indices.push_back(meshes[k].faces[i].mIndices[2]);
		}

		MeshRendererData meshRenderData;
		meshRenderData.mesh = std::make_shared<Mesh>(m_fileName + meshes[k].name, &vertices[0], vertices.size(), &indices[0], indices.size());
		meshRenderData.material = Materials[k];

		SkeletalAnimationModelLoader::sceneMeshRendererDataCache[m_fileName].push_back(meshRenderData);
		m_entity->addComponent<MeshRenderer>(meshRenderData.mesh, meshRenderData.material);
	}
}

//*/

void SkeletalAnimationModelLoader::read_Meshes_Channels_Bones(const aiScene *scene)
{
  //////////////////////////////////////////////////////////////////
  //     Read vertices, normals, texture coordinates
  //////////////////////////////////////////////////////////////////
  for (unsigned int cm = 0; cm < scene->mNumMeshes; cm++)
  {
    this->meshes.emplace_back();

    const aiMesh *mesh = scene->mMeshes[cm];
    meshes[cm].name = mesh->mName.C_Str();
    meshes[cm].materialId = mesh->mMaterialIndex;
    meshes[cm].vertices.resize(mesh->mNumVertices);
    meshes[cm].normals.resize(mesh->mNumVertices);
    meshes[cm].tangents.resize(mesh->mNumVertices);
    meshes[cm].textureCoords.resize(mesh->mNumVertices);

    const aiVector3D aiZeroVector(0.0f, 0.0f, 0.0f);
    for (unsigned int cv = 0; cv < mesh->mNumVertices; cv++)
    {
      meshes[cm].vertices[cv] = mesh->mVertices[cv];
      meshes[cm].normals[cv] = mesh->mNormals[cv];
      meshes[cm].tangents[cv] = mesh->HasTangentsAndBitangents() ? mesh->mTangents[cv] : aiZeroVector;

      if (mesh->HasTextureCoords(0))
      {
        meshes[cm].textureCoords[cv].x = mesh->mTextureCoords[0][cv].x;
        meshes[cm].textureCoords[cv].y = mesh->mTextureCoords[0][cv].y;
      }
      else
        meshes[cm].textureCoords[cv].x = meshes[cm].textureCoords[cv].y = 0.0;
    }
    meshes[cm].faces.resize(mesh->mNumFaces);
    for (unsigned int cf = 0; cf < mesh->mNumFaces; cf++)
    {
      meshes[cm].faces[cf] = mesh->mFaces[cf];
    }
  }
  ///////////////////////////////////////////////////////
  // Find channels, and the bones used in the channels
  ///////////////////////////////////////////////////////
  for (unsigned int ca = 0; ca < scene->mNumAnimations; ca++)
  {
    animations.emplace_back();
    auto &animation = animations[ca];

    animation.duration = scene->mAnimations[ca]->mDuration;
    animation.ticksPerSecond = scene->mAnimations[ca]->mTicksPerSecond;

    animation.channels.resize(scene->mAnimations[ca]->mNumChannels);
    for (unsigned int cc = 0; cc < scene->mAnimations[ca]->mNumChannels; cc++)
    {
      animation.channels[cc].positions.resize(scene->mAnimations[ca]->mChannels[cc]->mNumPositionKeys);
      animation.channels[cc].scales.resize(scene->mAnimations[ca]->mChannels[cc]->mNumScalingKeys);
      animation.channels[cc].rotations.resize(scene->mAnimations[ca]->mChannels[cc]->mNumRotationKeys);

      for (unsigned int cp = 0; cp < scene->mAnimations[ca]->mChannels[cc]->mNumPositionKeys; cp++)
      {
        animation.channels[cc].positions[cp] = scene->mAnimations[ca]->mChannels[cc]->mPositionKeys[cp];
      }
      for (unsigned int cs = 0; cs < scene->mAnimations[ca]->mChannels[cc]->mNumScalingKeys; cs++)
      {
        animation.channels[cc].scales[cs] = scene->mAnimations[ca]->mChannels[cc]->mScalingKeys[cs];
      }
      for (unsigned int cr = 0; cr < scene->mAnimations[ca]->mChannels[cc]->mNumRotationKeys; cr++)
      {
        animation.channels[cc].rotations[cr] = scene->mAnimations[ca]->mChannels[cc]->mRotationKeys[cr];
      }

      const aiNode *node = scene->mRootNode->FindNode(scene->mAnimations[ca]->mChannels[cc]->mNodeName);
      animations[ca].channels[cc].boneId = getBoneId(node);
    }
    //log_info("Majid: %i", 372);
  }

  ///////////////////////////////////////////////////////////////////////
  // Find all the bones, and their parent bones, connected to the meshes
  ///////////////////////////////////////////////////////////////////////
  for (unsigned int cm = 0; cm < scene->mNumMeshes; cm++)
  {
    for (unsigned int cb = 0; cb < scene->mMeshes[cm]->mNumBones; cb++)
    {
      const aiNode *node = scene->mRootNode->FindNode(scene->mMeshes[cm]->mBones[cb]->mName);
      this->meshes[cm].boneWeights.emplace_back();
      unsigned int boneId = getBoneId(node);
      this->meshes[cm].boneWeights[cb].boneId = boneId;
      this->meshes[cm].boneWeights[cb].offsetMatrix = scene->mMeshes[cm]->mBones[cb]->mOffsetMatrix;

      for (unsigned int cw = 0; cw < scene->mMeshes[cm]->mBones[cb]->mNumWeights; cw++)
      {
        this->meshes[cm].boneWeights[cb].weights.emplace_back(scene->mMeshes[cm]->mBones[cb]->mWeights[cw]);
      }

      if (!bones[boneId].hasParentBoneId)
      {
        //Populate Bone::parentBoneIds
        node = node->mParent;
        while (node != scene->mRootNode)
        {
          unsigned int parentBoneId = getBoneId(node);
          bones[boneId].parentBoneId = parentBoneId;
          bones[boneId].hasParentBoneId = true;
          boneId = parentBoneId;

          node = node->mParent;
        }
      }
    }
    //log_info("Majid: %i", 403);
  }
}
