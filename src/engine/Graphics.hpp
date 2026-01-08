#pragma once
#include <SDL3/SDL.h>

class Graphics {
public:
  explicit Graphics(SDL_Renderer *renderer) : m_Renderer(renderer) {}

  void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
    SDL_SetRenderDrawColor(m_Renderer, r, g, b, a);
  }

  void Clear() { SDL_RenderClear(m_Renderer); }

private:
  SDL_Renderer *m_Renderer;
};
