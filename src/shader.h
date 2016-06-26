#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>

class Shader {
public:
  Shader(const std::string &filename);
  void bind();
  virtual ~Shader();

protected:
private:
  static const unsigned int NUM_SHADERS = 2;
  GLuint m_program;
  GLuint m_shaders[NUM_SHADERS];
  Shader(const Shader &other);
  void operator=(const Shader &other);
};
#endif /* end of include guard: SHADER_H */
