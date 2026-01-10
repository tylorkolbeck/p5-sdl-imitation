#pragma once
#include "SDL3_gfxPrimitives.h"
#include <SDL3/SDL.h>
#include <cmath>

const float PI = 3.14159265358979323846264338327950288419716939937510f;

struct Color {
  int r = 0;
  int g = 0;
  int b = 0;
  int a = 255;
};

class Graphics {
public:
  explicit Graphics(SDL_Renderer *renderer) : m_Renderer(renderer) {}

  void Background(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
    Clear(r, g, b, a);
  }

  void Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
    m_CurrentColor = {r, g, b, a};
    SDL_SetRenderDrawColor(m_Renderer, r, g, b, a);
  }

  void Clear(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
    SDL_SetRenderDrawColor(m_Renderer, r, g, b, a);
    SDL_RenderClear(m_Renderer);
  }

  // 2d shapes
  void Line(float x1, float y1, float x2, float y2) {
    aalineRGBA(m_Renderer, x1, y1, x2, y2, m_CurrentColor.r, m_CurrentColor.g,
               m_CurrentColor.b, m_CurrentColor.a);
  }

  void Circle(float centerX, float centerY, float radius) {
    aacircleRGBA(m_Renderer, centerX, centerY, radius, m_CurrentColor.r,
                 m_CurrentColor.g, m_CurrentColor.b, m_CurrentColor.a);
  }

  void Rect(float x, float y, float width, float height) {
    Line(x, y, x + width, y);
    Line(x + width, y, x + width, y + height);
    Line(x + width, y + height, x, y + height);
    Line(x, y + height, x, y);
  }

private:
  struct Color m_CurrentColor;
  SDL_Renderer *m_Renderer;
};
