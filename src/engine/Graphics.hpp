#pragma once
#include "SDL3_gfxPrimitives.h"
#include <SDL3/SDL.h>
#include <cmath>
#include <cstdint>
#include <sys/types.h>

const float PI = 3.14159265358979323846264338327950288419716939937510f;
struct RGBA {
  uint8_t r, g, b, a = 255;
};

class Graphics {
public:
  explicit Graphics(SDL_Renderer *renderer) : m_Renderer(renderer) {}

  void Background(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
    Clear(r, g, b, a);
  }

  void Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
    m_StrokeColor = {r, g, b, a};
    SDL_SetRenderDrawColor(m_Renderer, r, g, b, a);
  }

  void Fill(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
    m_FillColor = {r, g, b, a};
    m_HasFill = true;
  }

  void Clear(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
    SDL_SetRenderDrawColor(m_Renderer, r, g, b, a);
    SDL_RenderClear(m_Renderer);
  }

  static inline float SnapToHalfPixel(float v) { return std::floor(v) + 0.5f; }

  // 2d shapes
  void Line(float x1, float y1, float x2, float y2) {
    if (m_StrokeWeight % 2 == 0) {
      x1 = SnapToHalfPixel(x1);
      y1 = SnapToHalfPixel(y1);
      x2 = SnapToHalfPixel(x2);
      y2 = SnapToHalfPixel(y2);
    }

    thickLineRGBA(m_Renderer, (Sint16)std::lround(x1), (Sint16)std::lround(y1),
                  (Sint16)std::lround(x2), (Sint16)std::lround(y2),
                  (Uint8)m_StrokeWeight, m_StrokeColor.r, m_StrokeColor.g,
                  m_StrokeColor.b, m_StrokeColor.a);
  }

  void Circle(float cx, float cy, float r) {
    const float half = m_StrokeWeight * 0.5f;

    // Outer radius of stroke
    const float outer = r + half;
    // Inner radius of stroke
    const float inner = std::max(0.0f, r - half);

    // 1) Stroke as solid outer disk
    if (m_HasStroke && m_StrokeWeight > 0) {
      filledCircleRGBA(m_Renderer, (Sint16)cx, (Sint16)cy,
                       (Sint16)std::round(outer), m_StrokeColor.r,
                       m_StrokeColor.g, m_StrokeColor.b, m_StrokeColor.a);
    }

    // 2) Fill disk on top
    if (m_HasFill) {
      filledCircleRGBA(m_Renderer, (Sint16)cx, (Sint16)cy,
                       (Sint16)std::round(inner), m_FillColor.r, m_FillColor.g,
                       m_FillColor.b, m_FillColor.a);
    }
  }
  void Point(float x, float y) {
    filledCircleRGBA(m_Renderer, x, y, 1 * m_PointSize, m_StrokeColor.r,
                     m_StrokeColor.g, m_StrokeColor.b, m_StrokeColor.a);
  }

  void PointSize(int value) { m_PointSize = value; }

  void Rect(float x, float y, float w, float h) {
    // --- Fill ---
    if (m_HasFill) {
      boxRGBA(m_Renderer, x, y, x + w, y + h, m_FillColor.r, m_FillColor.g,
              m_FillColor.b, m_FillColor.a);
    }

    // --- Stroke ---
    if (m_HasStroke && m_StrokeWeight > 0) {
      int s = m_StrokeWeight;
      float half = s * 0.5f;

      // Top
      boxRGBA(m_Renderer, x - half, y - half, x + w + half, y + half,
              m_StrokeColor.r, m_StrokeColor.g, m_StrokeColor.b,
              m_StrokeColor.a);

      // Bottom
      boxRGBA(m_Renderer, x - half, y + h - half, x + w + half, y + h + half,
              m_StrokeColor.r, m_StrokeColor.g, m_StrokeColor.b,
              m_StrokeColor.a);

      // Left
      boxRGBA(m_Renderer, x - half, y, x + half, y + h, m_StrokeColor.r,
              m_StrokeColor.g, m_StrokeColor.b, m_StrokeColor.a);

      // Right
      boxRGBA(m_Renderer, x + w - half, y, x + w + half, y + h, m_StrokeColor.r,
              m_StrokeColor.g, m_StrokeColor.b, m_StrokeColor.a);
    }
  }

  // Environment
  int Width() { return m_Width; }
  int Height() { return m_Height; }

  // Settings
  void Stroke(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
    m_StrokeColor = {r, g, b, a};
    m_HasStroke = true;
  }

  void StrokeWeight(int w) { m_StrokeWeight = std::max(1, w); }

  void NoStroke() { m_HasStroke = false; }

  void NoFill() { m_HasFill = false; }

private:
  friend class Canvas;
  void SetSize(int w, int h) {
    m_Width = w;
    m_Height = h;
  }
  RGBA m_StrokeColor{255, 255, 255, 255};
  RGBA m_FillColor{255, 255, 255, 255};
  int m_StrokeWeight = 1;
  bool m_HasStroke = true;
  bool m_HasFill = true;
  int m_PointSize = 1;
  SDL_Renderer *m_Renderer;
  int m_Width = 1;
  int m_Height = 1;
};
