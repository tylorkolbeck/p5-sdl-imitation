#include "Walker.hpp"
#include "engine/Graphics.hpp"

Walker::Walker(float x, float y) : m_X(x), m_Y(y) {}
Walker::Walker() : m_X(0), m_Y(0) {}

void Walker::Update(float dt) {}

void Walker::AddX(float value) { m_X += value; }

void Walker::AddY(float value) { m_Y += value; }

void Walker::Render(Graphics &g) const {
  g.PointSize(6);
  g.Point(m_X, m_Y);
}
