#pragma once
#include "engine/Entity.hpp"

class Walker : public Entity {
public:
  Walker(float x, float y);
  Walker();

  void Update(float dt) override;
  void Render(Graphics &g) const override;

  void AddX(float value) override;
  void AddY(float value) override;

  float m_X, m_Y = 0.0f;

private:
};
