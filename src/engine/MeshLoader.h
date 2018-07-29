//
//  Author: Shervin Aflatooni
//

#pragma once

#include <unordered_map>
#include "Material.h"
#include "Texture.h"
#include "Mesh.h"

#include "Entity.h"
#include <string>
#include <map>
#include <vector>

#include <assimp/scene.h>

struct MeshRendererData
{
  std::shared_ptr<Mesh> mesh;
  std::shared_ptr<Material> material;
};

class MeshLoader
{
public:
  MeshLoader(const std::string file);
  MeshLoader() {}
  ~MeshLoader(void) {}

  std::shared_ptr<Entity> getEntity(void) const;

protected:
  void loadScene(const aiScene *scene);

  std::string m_fileName;

  std::shared_ptr<Entity> m_entity;

  static std::map<std::string, std::vector<MeshRendererData>> sceneMeshRendererDataCache;
};

//////Added by Majid Anjidani////////////////////////////////
class Bone
{
public:
  aiMatrix4x4 transformation;

  unsigned int parentBoneId;
  bool hasParentBoneId;

  Bone() : hasParentBoneId(false) {}
};

class BoneWeights
{
public:
  aiMatrix4x4 offsetMatrix;
  std::vector<aiVertexWeight> weights;

  unsigned int boneId;
};

class Animation
{
public:
  class Channel
  {
  public:
    unsigned int boneId;

    std::vector<aiVectorKey> positions;
    std::vector<aiQuatKey> rotations;
    std::vector<aiVectorKey> scales;
  };

  double duration;
  double ticksPerSecond;

  std::vector<Channel> channels;

private:
  aiVector3D interpolateFunction(const aiVector3D &beforeMatrix, const aiVector3D &afterMatrix, double factor) const
  {
    aiVector3D diffMatrix = afterMatrix - beforeMatrix;
    diffMatrix *= factor;

    return beforeMatrix + diffMatrix;
  }
  aiQuaternion interpolateFunction(const aiQuaternion &beforeMatrix, const aiQuaternion &afterMatrix, double factor) const
  {
    aiQuaternion returnMatrix;
    aiQuaternion::Interpolate(returnMatrix, beforeMatrix, afterMatrix, factor);

    return returnMatrix;
  }

public:
  //time in seconds
  template <class KeyType>
  auto interpolate(const std::vector<KeyType> &keys, double time, bool loop = true) const -> decltype(keys.begin()->mValue)
  {
    time *= ticksPerSecond;

    if (loop)
    {
      time = fmod(time, duration);
    }
    else if (time >= duration)
    {
      return keys[keys.size() - 1].mValue;
    }

    unsigned int keyBefore = 0, keyAfter = 0;
    double frameDuration = 1.0, frameTime = 0.0;
    for (unsigned int cv = 0; cv < keys.size(); cv++)
    {
      if (time < keys[cv].mTime)
      {
        keyAfter = cv;
        if (cv == 0)
        {
          keyBefore = keys.size() - 1;
          frameDuration = keys[0].mTime;
          frameTime = time;
        }
        else
        {
          keyBefore = cv - 1;
          frameDuration = keys[keyAfter].mTime - keys[keyBefore].mTime;
          frameTime = time - keys[keyBefore].mTime;
        }
        break;
      }
    }

    double factor = frameTime / frameDuration;

    return interpolateFunction(keys[keyBefore].mValue, keys[keyAfter].mValue, factor);
  }
};

class MeshExtended
{
public:
  std::vector<aiVector3D> vertices;
  std::vector<aiVector3D> normals;
  std::vector<aiVector3D> tangents;
  std::vector<aiVector2D> textureCoords;
  std::vector<aiFace> faces;
  std::vector<BoneWeights> boneWeights;
  //In AssImp: one material per mesh
  unsigned int materialId;
  std::string name;
};

class SkeletalAnimationModelLoader : public MeshLoader
{
public:
  SkeletalAnimationModelLoader(const std::string file, glm::quat rotation = glm::quat(), float scal = 1.0);
  ~SkeletalAnimationModelLoader(void) {}

  ///////////////////////
  class MeshFrame
  {
  public:
    std::vector<aiVector3D> vertices;
    std::vector<aiVector3D> normals;
    std::vector<aiVector3D> tangents;

    const MeshExtended &mesh;

    MeshFrame(const MeshExtended &mesh) : vertices(mesh.vertices.size()), normals(mesh.normals.size()), tangents(mesh.tangents.size()), mesh(mesh) {}
  };
  ///////////////////////
  aiMatrix4x4 aiMatrix4x4Compose(const aiVector3D &scaling, const aiQuaternion &rotation, const aiVector3D &position)
  {
    aiMatrix4x4 r;

    aiMatrix3x3 m = rotation.GetMatrix();

    r.a1 = m.a1 * scaling.x;
    r.a2 = m.a2 * scaling.x;
    r.a3 = m.a3 * scaling.x;
    r.a4 = position.x;

    r.b1 = m.b1 * scaling.y;
    r.b2 = m.b2 * scaling.y;
    r.b3 = m.b3 * scaling.y;
    r.b4 = position.y;

    r.c1 = m.c1 * scaling.z;
    r.c2 = m.c2 * scaling.z;
    r.c3 = m.c3 * scaling.z;
    r.c4 = position.z;

    r.d1 = 0.0;
    r.d2 = 0.0;
    r.d3 = 0.0;
    r.d4 = 1.0;

    return r;
  }
  MeshFrame getMeshFrame(const MeshExtended &mesh) const;
  void createFrame(unsigned int animationId, double time, bool loop = true);
  void loadNewFrame(unsigned int animationId, double time);
  //void loadscene();//(unsigned int animationId, double time)
private:
  aiMatrix4x4 transformation;
  //Add bone if it does not yet exist, and return boneId
  std::vector<MeshExtended> meshes;
  //std::vector<std::shared_ptr<Material>> Materials;
  std::vector<Animation> animations;
  std::vector<Bone> bones;
  std::unordered_map<std::string, unsigned int> boneName2boneId;
  unsigned int getBoneId(const aiNode *node)
  {
    unsigned int boneId;
    if (boneName2boneId.count(node->mName.data) == 0)
    {
      bones.emplace_back();
      boneId = bones.size() - 1;
      boneName2boneId[node->mName.data] = boneId;

      bones[boneId].transformation = node->mTransformation;
    }
    else
    {
      boneId = boneName2boneId[node->mName.data];
    }

    return boneId;
  }
  void read_Meshes_Channels_Bones(const aiScene *scene);
};
