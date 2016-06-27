#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <glm/glm.hpp>

class Vertex {
public:
  Vertex(const glm::vec3 &pos, const glm::vec2 &textCoord) {
    this->pos = pos;
    this->textCoord = textCoord;
  }

  inline glm::vec3 getPos() { return this->pos; }
  inline glm::vec2 getTextCoord() { return this->textCoord; }

protected:
private:
  glm::vec3 pos;
  glm::vec2 textCoord;
};

class Mesh {
public:
  Mesh(Vertex *vertices, unsigned int numVertices);
  virtual ~Mesh();
  void draw();

private:
  Mesh(const Mesh &other);
  Mesh &operator=(const Mesh &other);

  enum { POSITION_VB, TEXTCOORD_VB, NUM_BUFFERS };

  GLuint m_vertexArrayObject;
  GLuint m_vertexArrayBuffers[NUM_BUFFERS];
  unsigned int m_drawCount;
};

#endif /* end of include guard: MESH_H */
