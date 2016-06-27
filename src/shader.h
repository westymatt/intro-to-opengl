#ifndef SHADER_H
#define SHADER_H

#include "transform.h"
#include <GL/glew.h>
#include <string>

class Shader {
public:
  Shader(const std::string &filename);
  void bind();
  void update(const Transform &transform);
  virtual ~Shader();

protected:
private:
  enum { TRANSFORM_U, NUM_UNIFORMS };
  static const unsigned int NUM_SHADERS = 2;
  GLuint m_program;
  GLuint m_shaders[NUM_SHADERS];
  GLuint m_uniforms[NUM_UNIFORMS];
  Shader(const Shader &other);
  void operator=(const Shader &other);
};
#endif /* end of include guard: SHADER_H */
