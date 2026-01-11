#pragma once
#include "Sketch.hpp"
#include <SDL3/SDL.h>

struct WindowProps {
  int Width;
  int Height;
  const char *AppVersion;
  const char *Title;
};

class Canvas {
public:
  explicit Canvas(const WindowProps &props);
  ~Canvas();
  SDL_Window *Window() const { return m_Window; };
  SDL_Renderer *Renderer() const { return m_Renderer; };
  bool Run(Sketch &sketch);

private:
  bool Init();
  SDL_Window *m_Window;
  SDL_Renderer *m_Renderer;
  int m_Width;
  int m_Height;
  const char *m_AppVersion;
  const char *m_Title;
};
