#include "Walker.hpp"
#include "engine/Graphics.hpp"
#include "engine/util/Rand.hpp"
#include <cmath>

using namespace util::random;

Walker::Walker(Vec pos) : Entity(pos) {}
Walker::Walker() : Entity(Vec{}) {}

void Walker::Update(float dt) {
  m_Velocity += m_Acceleration * dt;
  m_Velocity.Limit(m_MaxSpeed);
  m_Pos += m_Velocity * dt;

  m_Acceleration = {0.0f, 0.0f, 0.0f};
}

void Walker::Render(Graphics &g) const {
  g.PointSize(6);
  g.Point(m_Pos.x, m_Pos.y);
}
