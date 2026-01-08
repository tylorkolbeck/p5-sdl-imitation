#pragma once
#include <SDL3/SDL.h>

struct WindowProps {
  int Width;
  int Height;
  const char *Title;
};

class Canvas {
public:
  explicit Canvas(const WindowProps &props);
  ~Canvas();
  SDL_Window *Window() const { return m_Window; };
  SDL_Renderer *Renderer() const { return m_Renderer; };
  bool Run();

private:
  bool Init();
  WindowProps m_WindowProps;
  SDL_Window *m_Window;
  SDL_Renderer *m_Renderer;
};
