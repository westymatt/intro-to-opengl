#include "display.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "transform.h"
#include <GL/glew.h>

#include <iostream>

int main() {
  Display display(800, 600, "Hello World");

  Shader shader("./res/basicShader");

  Vertex vertices[] = {Vertex(glm::vec3(-0.5, -0.5, 0.0), glm::vec2(0, 0)),
                       Vertex(glm::vec3(0.0, 0.5, 0.0), glm::vec2(0.5, 1.0)),
                       Vertex(glm::vec3(0.5, -0.5, 0.0), glm::vec2(1.0, 0))};

  Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));
  Texture texture("./res/bricks.jpg");
  Transform transform;

  float counter = 0.0f;
  while (!display.isClosed()) {
    display.clear(0.0f, 0.15f, 0.3f, 1.0f);

    float sinCounter = sinf(counter);
    float cosCounter = cosf(counter);

    transform.getPos().x = sinCounter;
    transform.getRot().z = counter * 50;
    transform.setScale(glm::vec3(cosCounter, cosCounter, cosCounter));

    shader.bind();
    shader.update(transform);
    texture.bind(0);
    mesh.draw();

    display.update();
    counter += 0.01f;
  }

  return 0;
}
