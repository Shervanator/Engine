#include "Mesh.h"

#include "Logger.h"

#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#define check_gl_error() { \
  { \
    GLenum err; \
    while ((err = glGetError()) != GL_NO_ERROR) { \
        log_err("OpenGL error: %s", err); \
    } \
  } \
} \

Mesh::Mesh(Vertex vertices[], int vertSize, unsigned int indices[], int indexSize)
{
  createMesh(vertices, vertSize, indices, indexSize);
}

Mesh::Mesh(Asset file)
{
  Assimp::Importer importer;
  // log_info("Loading mesh: %s, data: %s", file.getFileName().c_str(), file.read());

  const aiScene* scene = importer.ReadFileFromMemory(file.read(), file.getSize(),
                                                     aiProcess_Triangulate |
                                                     aiProcess_GenSmoothNormals |
                                                     aiProcess_FlipUVs |
                                                     aiProcess_CalcTangentSpace);

  if(!scene)
  {
    log_err("Failed to load mesh: %s", file.getFileName().c_str());
  }

  const aiMesh* model = scene->mMeshes[0];

  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;

  const aiVector3D aiZeroVector(0.0f, 0.0f, 0.0f);
  for(unsigned int i = 0; i < model->mNumVertices; i++)
  {
    const aiVector3D* pPos = &(model->mVertices[i]);
    const aiVector3D* pNormal = &(model->mNormals[i]);
    const aiVector3D* pTexCoord = model->HasTextureCoords(0) ? &(model->mTextureCoords[0][i]) : &aiZeroVector;
    const aiVector3D* pTangent = &(model->mTangents[i]);

    Vertex vert(glm::vec3(pPos->x, pPos->y, pPos->z),
                glm::vec2(pTexCoord->x, pTexCoord->y),
                glm::vec3(pNormal->x, pNormal->y, pNormal->z),
                glm::vec3(pTangent->x, pTangent->y, pTangent->z));

    vertices.push_back(vert);
  }

  for(unsigned int i = 0; i < model->mNumFaces; i++)
  {
    const aiFace& face = model->mFaces[i];
    log_info("index: %u %u %u", face.mIndices[0], face.mIndices[1], face.mIndices[2]);
    indices.push_back(face.mIndices[0]);
    indices.push_back(face.mIndices[1]);
    indices.push_back(face.mIndices[2]);
  }

  createMesh(&vertices[0], vertices.size(), &indices[0], indices.size());
}

Mesh::~Mesh(void)
{
  glDeleteBuffers(1, &vbo);
#if !defined(GLES2)
  glDeleteVertexArrays(1, &vao);
#endif
}

void Mesh::createMesh(Vertex vertices[], int vertSize, unsigned int indices[], int indexSize)
{
  log_info("Creating mesh, number of verts: %i, number of indicies: %i", vertSize, indexSize);
  this->vertSize  = vertSize;
  this->indexSize = indexSize;

#if !defined(GLES2)
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
#endif

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, vertSize * sizeof(Vertex), vertices, GL_STATIC_DRAW);

  glGenBuffers(1, &ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize * sizeof(unsigned int), indices, GL_STATIC_DRAW);

#if !defined(GLES2)
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)sizeof(glm::vec3));

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(glm::vec3) + sizeof(glm::vec2)));

  glEnableVertexAttribArray(3);
  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(glm::vec3) + sizeof(glm::vec2) + sizeof(glm::vec3)));

  glBindVertexArray(0);
#endif
}

void Mesh::render(void)
{
#if defined(GLES2)
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)sizeof(glm::vec3));

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(glm::vec3) + sizeof(glm::vec2)));

  glEnableVertexAttribArray(3);
  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(glm::vec3) + sizeof(glm::vec2) + sizeof(glm::vec3)));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  glDrawElements(GL_POINTS, indexSize, GL_UNSIGNED_INT, (void*)0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
  glDisableVertexAttribArray(3);
#else
  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, (void*)0);
  glBindVertexArray(0);
#endif
}
