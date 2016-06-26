#include "mesh.h"
#include <iostream>

Mesh::Mesh(Vertex *vertices, unsigned int numVertices) {
  this->m_drawCount = numVertices;

  glGenVertexArrays(1, &this->m_vertexArrayObject);
  glBindVertexArray(this->m_vertexArrayObject);

  glGenBuffers(NUM_BUFFERS, this->m_vertexArrayBuffers);
  glBindBuffer(GL_ARRAY_BUFFER, this->m_vertexArrayBuffers[POSITION_VB]);
  glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(vertices[0]), vertices,
               GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glBindVertexArray(0);
}

Mesh::~Mesh() { glDeleteVertexArrays(1, &this->m_vertexArrayObject); }

void Mesh::draw() {
  glBindVertexArray(this->m_vertexArrayObject);
  glDrawArrays(GL_TRIANGLES, 0, this->m_drawCount);
  glBindVertexArray(0);
}
