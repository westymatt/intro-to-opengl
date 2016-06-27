#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <string>

class Texture {
public:
  Texture(const std::string &filename);
  virtual ~Texture();

  void bind(unsigned int unit);

protected:
private:
  Texture(const Texture &other);
  Texture &operator=(const Texture &other);

  GLuint m_texture;
};

#endif /* end of include guard: TEXTURE_H */
