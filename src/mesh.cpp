#include "mesh.h"
#include <iostream>
#include <vector>

Mesh::Mesh(const std::string &filename) {
  IndexedModel model = OBJModel(filename).ToIndexedModel();
  this->initMesh(model);
}

Mesh::Mesh(Vertex *vertices, unsigned int numVertices, unsigned int *indices,
           unsigned int numIndices) {
  IndexedModel model;

  for (unsigned int i = 0; i < numVertices; i++) {
    model.positions.push_back(*vertices[i].getPos());
    model.texCoords.push_back(*vertices[i].getTexCoord());
    model.normals.push_back(*vertices[i].getNormal());
  }

  for (unsigned int i = 0; i < numIndices; i++) {
    model.indices.push_back(indices[i]);
  }
  this->initMesh(model);
}

Mesh::~Mesh() { glDeleteVertexArrays(1, &this->m_vertexArrayObject); }

void Mesh::draw() {
  glBindVertexArray(this->m_vertexArrayObject);
  glDrawElements(GL_TRIANGLES, this->m_drawCount, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

void Mesh::initMesh(const IndexedModel &model) {
  this->m_drawCount = model.indices.size();
  glGenVertexArrays(1, &this->m_vertexArrayObject);
  glBindVertexArray(this->m_vertexArrayObject);

  glGenBuffers(NUM_BUFFERS, this->m_vertexArrayBuffers);
  glBindBuffer(GL_ARRAY_BUFFER, this->m_vertexArrayBuffers[POSITION_VB]);
  glBufferData(GL_ARRAY_BUFFER,
               model.positions.size() * sizeof(model.positions[0]),
               &model.positions[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ARRAY_BUFFER, this->m_vertexArrayBuffers[TEXTCOORD_VB]);
  glBufferData(GL_ARRAY_BUFFER,
               model.positions.size() * sizeof(model.texCoords[0]),
               &model.texCoords[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

  // new
  glBindBuffer(GL_ARRAY_BUFFER, this->m_vertexArrayBuffers[NORMAL_VB]);
  glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]),
               &model.normals[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_vertexArrayBuffers[INDEX_VB]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               model.indices.size() * sizeof(model.indices[0]),
               &model.indices[0], GL_STATIC_DRAW);

  glBindVertexArray(0);
}
