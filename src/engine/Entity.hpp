#pragma once

#include "SDL3/SDL_events.h"
#include "engine/util/Vec.hpp"
class Graphics;

class Entity {
public:
  Entity() = default;
  Entity(Vec pos) : m_Pos(pos) {};
  virtual ~Entity() = default;
  virtual void Setup() {}
  virtual void Update(float dt) = 0;
  virtual void Render(Graphics &g) const = 0;
  virtual void SetPos(float x, float y) {
    m_Pos.x = x;
    m_Pos.y = y;
  };

  const Vec &Pos() const { return m_Pos; }
  Vec &Pos() { return m_Pos; };
  const Vec &Velocity() const { return m_Velocity; }
  Vec &Vel() { return m_Velocity; }
  float &MaxSpeed() { return m_MaxSpeed; }
  virtual void OnEvent(const SDL_Event &) {}
  virtual void ApplyForce(Vec force) { m_Acceleration += force; }

protected:
  Vec m_Pos{};
  Vec m_Acceleration{};
  Vec m_Velocity{};
  float m_MaxSpeed = 50;

private:
};
