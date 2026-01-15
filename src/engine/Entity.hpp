#pragma once
#include "Position.hpp"

#include "SDL3/SDL_events.h"
class Graphics;

class Entity {
public:
  virtual ~Entity() = default;
  virtual void Setup() {}
  virtual void Update(float dt) = 0;
  virtual void Render(Graphics &g) const = 0;
  virtual void SetPos(float x, float y) {
    m_Pos.x = x;
    m_Pos.y = y;
  };

  virtual void OnEvent(const SDL_Event &) {}

  virtual void AddX(float) {};
  virtual void AddY(float) {};

private:
  Position m_Pos{0.0f, 0.0f};
};
