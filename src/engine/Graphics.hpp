#pragma once
#include <SDL3/SDL.h>
#include <cmath>

const float PI = 3.14159265358979323846264338327950288419716939937510f;

class Graphics {
public:
  explicit Graphics(SDL_Renderer *renderer) : m_Renderer(renderer) {}

  void Background(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
    Clear(r, g, b, a);
  }

  void Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
    SDL_SetRenderDrawColor(m_Renderer, r, g, b, a);
  }

  void Clear(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
    SDL_SetRenderDrawColor(m_Renderer, r, g, b, a);
    SDL_RenderClear(m_Renderer);
  }

  // 2d shapes
  void Line(float x1, float y1, float x2, float y2) {
    SDL_RenderLine(m_Renderer, x1, y1, x2, y2);
  }

  void Circle(float centerX, float centerY, float radius) {
    int sides = (int)(radius * 6.0f); // tweak this
    if (sides < 32)
      sides = 32;
    if (sides > 512)
      sides = 512;
    // int sides =
    //     static_cast<int>((2.0f * PI * radius) / 2.0f); // 1 segment per 2px
    if (sides < 10)
      sides = 10;

    float angle_inc = (2.0f * PI) / static_cast<float>(sides);
    for (int i = 0; i < sides; ++i) {
      float angle = i * angle_inc;
      float next_angle = (i + 1) * angle_inc;

      float x1 = centerX + radius * cos(angle);
      float y1 = centerY + radius * sin(angle);
      float x2 = centerX + radius * cos(next_angle);
      float y2 = centerY + radius * sin(next_angle);

      Line(x1, y1, x2, y2);
    }
  }

  void Rect(float x, float y, float width, float height) {
    Line(x, y, x + width, y);
    Line(x + width, y, x + width, y + height);
    Line(x + width, y + height, x, y + height);
    Line(x, y + height, x, y);
  }

private:
  SDL_Renderer *m_Renderer;
};
