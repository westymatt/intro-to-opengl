#include "display.h"
#include "mesh.h"
#include "shader.h"
#include <GL/glew.h>

#include <iostream>

int main() {
  Display display(800, 600, "Hello World");

  Shader shader("./res/basicShader");

  Vertex vertices[] = {Vertex(glm::vec3(-0.5, -0.5, 0.0)),
                       Vertex(glm::vec3(0.0, 0.5, 0.0)),
                       Vertex(glm::vec3(0.5, -0.5, 0.0))};

  Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));
  while (!display.isClosed()) {
    display.clear(0.0f, 0.15f, 0.3f, 1.0f);
    shader.bind();
    mesh.draw();

    display.update();
  }

  return 0;
}
