#pragma once
#include "engine/Entity.hpp"

class Walker : public Entity {
public:
  Walker(Vec pos);
  Walker();

  void Update(float dt) override;
  void Render(Graphics &g) const override;

private:
  float m_Speed = 10.0;
};
