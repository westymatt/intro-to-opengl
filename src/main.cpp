#include "display.h"
#include "shader.h"
#include <GL/glew.h>

#include <iostream>

int main() {
  Display display(800, 600, "Hello World");

  Shader shader("./res/basicShader");

  while (!display.isClosed()) {
    display.clear(0.0f, 0.15f, 0.3f, 1.0f);

    display.update();
  }

  return 0;
}
