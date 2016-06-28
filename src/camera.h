#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera {
public:
  Camera(const glm::vec3 &pos, float fov, float aspect, float zNear,
         float zFar) {
    this->m_perspective = glm::perspective(fov, aspect, zNear, zFar);
    this->m_position = pos;
    this->m_forward = glm::vec3(0, 0, 1);
    this->m_up = glm::vec3(0, 1, 0);
  }

  inline glm::mat4 getViewProjection() const {
    return this->m_perspective * glm::lookAt(this->m_position,
                                             this->m_position + this->m_forward,
                                             this->m_up);
  }

private:
  glm::mat4 m_perspective;
  glm::vec3 m_position;
  glm::vec3 m_forward;
  glm::vec3 m_up;
};
#endif /* end of include guard: CAMERA_H */
