#ifndef MESH_H
#define MESH_H

#include "obj_loader.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

class Vertex {
public:
  Vertex(const glm::vec3 &pos, const glm::vec2 &texCoord,
         const glm::vec3 &normal = glm::vec3(0, 0, 0)) {
    this->pos = pos;
    this->texCoord = texCoord;
    this->normal = normal;
  }

  inline glm::vec3 *getPos() { return &this->pos; }
  inline glm::vec2 *getTexCoord() { return &this->texCoord; }
  inline glm::vec3 *getNormal() { return &this->normal; }

protected:
private:
  glm::vec3 pos;
  glm::vec2 texCoord;
  glm::vec3 normal;
};

class Mesh {
public:
  Mesh(Vertex *vertices, unsigned int numVertices, unsigned int *indices,
       unsigned int numIndices);
  Mesh(const std::string &filename);
  virtual ~Mesh();
  void draw();
  void initMesh(const IndexedModel &model);

private:
  Mesh(const Mesh &other);
  Mesh &operator=(const Mesh &other);

  enum { POSITION_VB, TEXTCOORD_VB, NORMAL_VB, INDEX_VB, NUM_BUFFERS };

  GLuint m_vertexArrayObject;
  GLuint m_vertexArrayBuffers[NUM_BUFFERS];
  unsigned int m_drawCount;
};

#endif /* end of include guard: MESH_H */
