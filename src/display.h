#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <string>

class Display {
public:
  Display(int width, int height, const std::string &title);
  void clear(float r, float g, float b, float a);
  void update();

  bool isClosed();

  virtual ~Display();

protected:
private:
  void operator=(const Display &display){};
  Display(const Display &display){};

  SDL_Window *m_window;
  SDL_GLContext m_glContext;
  bool m_isClosed = false;
};
#endif /* end of include guard: DISPLAY_H */
