#include "mesh.h"
#include <iostream>
#include <vector>

Mesh::Mesh(Vertex *vertices, unsigned int numVertices) {
  this->m_drawCount = numVertices;

  glGenVertexArrays(1, &this->m_vertexArrayObject);
  glBindVertexArray(this->m_vertexArrayObject);

  std::vector<glm::vec3> positions;
  std::vector<glm::vec2> textCoords;

  positions.reserve(numVertices);
  textCoords.reserve(numVertices);

  for (int i = 0; i < numVertices; i++) {
    positions.push_back(vertices[i].getPos());
    textCoords.push_back(vertices[i].getTextCoord());
  }

  glGenBuffers(NUM_BUFFERS, this->m_vertexArrayBuffers);
  glBindBuffer(GL_ARRAY_BUFFER, this->m_vertexArrayBuffers[POSITION_VB]);
  glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]),
               &positions[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ARRAY_BUFFER, this->m_vertexArrayBuffers[TEXTCOORD_VB]);
  glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(textCoords[0]),
               &textCoords[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

  glBindVertexArray(0);
}

Mesh::~Mesh() { glDeleteVertexArrays(1, &this->m_vertexArrayObject); }

void Mesh::draw() {
  glBindVertexArray(this->m_vertexArrayObject);
  glDrawArrays(GL_TRIANGLES, 0, this->m_drawCount);
  glBindVertexArray(0);
}
