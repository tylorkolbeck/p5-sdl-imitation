#pragma once
#include "engine/Entity.hpp"
#include "engine/Sketch.hpp"
#include <memory>
#include <vector>

class RandomnessSketch : public Sketch {
public:
  RandomnessSketch() = default;
  void Setup() override;
  void Update(float dt) override;
  void Draw() override;
  void OnEvent(const SDL_Event &e) override;

private:
  std::vector<std::unique_ptr<Entity>> m_Entities = {};
};
