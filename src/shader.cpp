#include "shader.h"
#include <fstream>
#include <iostream>

static GLuint createShader(const std::string &text, GLenum shaderType);
static void checkShaderError(GLuint shader, GLuint flat, bool isProgram,
                             const std::string &errorMessage);
static std::string loadShader(const std::string &filename);

Shader::Shader(const std::string &filename) {
  this->m_program = glCreateProgram();
  this->m_shaders[0] =
      createShader(loadShader(filename + ".vs"), GL_VERTEX_SHADER);
  this->m_shaders[1] =
      createShader(loadShader(filename + ".fs"), GL_FRAGMENT_SHADER);

  for (unsigned int i = 0; i < this->NUM_SHADERS; i++) {
    glAttachShader(this->m_program, m_shaders[i]);
  }

  glBindAttribLocation(this->m_program, 0, "position");

  glLinkProgram(this->m_program);
  checkShaderError(this->m_program, GL_LINK_STATUS, true,
                   "Error shader program failed to link");
  glValidateProgram(this->m_program);
  checkShaderError(this->m_program, GL_VALIDATE_STATUS, true,
                   "Error program is invalid");
}

Shader::~Shader() {
  for (unsigned int i = 0; i < this->NUM_SHADERS; i++) {
    glDetachShader(this->m_program, this->m_shaders[i]);
    glDeleteShader(this->m_shaders[i]);
  }
  glDeleteProgram(this->m_program);
}

static std::string loadShader(const std::string &filename) {
  std::ifstream file;
  file.open(filename.c_str());

  std::string output;
  std::string line;

  if (file.is_open()) {
    while (file.good()) {
      getline(file, line);
      output.append(line + '\n');
    }
  } else {
    std::cerr << "Unable to load shader" << filename << std::endl;
  }
  return output;
}

void Shader::bind() { glUseProgram(this->m_program); }

static void checkShaderError(GLuint shader, GLuint flag, bool isProgram,
                             const std::string &errorMessage) {
  GLint success = 0;
  GLchar error[1024] = {0};
  if (isProgram) {
    glGetProgramiv(shader, flag, &success);
  } else {
    glGetShaderiv(shader, flag, &success);
  }

  if (success == GL_FALSE) {
    if (isProgram) {
      glGetProgramInfoLog(shader, sizeof(error), NULL, error);
    } else {
      glGetShaderInfoLog(shader, sizeof(error), NULL, error);
    }
    std::cerr << errorMessage << ": " << error << std::endl;
  }
}

static GLuint createShader(const std::string &text, GLenum shaderType) {
  GLuint shader = glCreateShader(shaderType);
  if (shader == 0) {
    std::cerr << "Error shader creation failed" << std::endl;
  }

  const GLchar *shaderSourceStrings[1];
  GLint shaderSourceStringLengths[1];

  shaderSourceStrings[0] = text.c_str();
  shaderSourceStringLengths[0] = text.length();

  glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
  glCompileShader(shader);
  checkShaderError(shader, GL_COMPILE_STATUS, false,
                   "Error shader compilation error");
  return shader;
}
