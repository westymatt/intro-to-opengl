#include "camera.h"
#include "display.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "transform.h"
#include <GL/glew.h>

#include <iostream>

#define WIDTH 800
#define HEIGHT 600

int main() {
  Display display(WIDTH, HEIGHT, "Hello World");

  Shader shader("./res/basicShader");

  Vertex vertices[] = {Vertex(glm::vec3(-0.5, -0.5, 0.0), glm::vec2(0, 0)),
                       Vertex(glm::vec3(0.0, 0.5, 0.0), glm::vec2(0.5, 1.0)),
                       Vertex(glm::vec3(0.5, -0.5, 0.0), glm::vec2(1.0, 0))};

  unsigned int indices[] = {0, 1, 2};

  Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices,
            sizeof(indices) / sizeof(indices[0]));
  Mesh mesh2("./res/monkey3.obj");
  Texture texture("./res/bricks.jpg");
  Transform transform;
  Camera camera(glm::vec3(0, 0, -3), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f,
                1000.0f);

  float counter = 0.0f;
  while (!display.isClosed()) {
    display.clear(0.0f, 0.15f, 0.3f, 1.0f);

    float sinCounter = sinf(counter);
    float cosCounter = cosf(counter);

    transform.getPos().x = sinCounter;
    transform.getPos().z = cosCounter;
    transform.getRot().z = counter * 1;
    transform.getRot().y = counter * 1;
    transform.getRot().x = counter * 1;
    // transform.setScale(glm::vec3(cosCounter, cosCounter, cosCounter));

    shader.bind();
    shader.update(transform, camera);
    texture.bind(0);
    // mesh.draw();
    mesh2.draw();

    display.update();
    counter += 0.0099999f;
  }

  return 0;
}
