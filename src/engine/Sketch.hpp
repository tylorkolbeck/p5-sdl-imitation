#pragma once
#include "engine/Graphics.hpp"
#include <SDL3/SDL.h>

class Sketch {
public:
  virtual ~Sketch() = default;
  virtual void Setup() {};
  virtual void Update(float dt) { (void)dt; };
  virtual void Draw() = 0;
  virtual void OnEvent(const SDL_Event &e) { (void)e; };

  void Background(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
    m_Graphics->SetColor(r, g, b, a);
  }

  void Clear() { m_Graphics->Clear(); }

protected:
  Graphics &G() { return *m_Graphics; };

private:
  friend class Canvas;
  Graphics *m_Graphics = nullptr;
};
