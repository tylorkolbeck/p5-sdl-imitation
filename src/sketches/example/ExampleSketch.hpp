#pragma once
#include "engine/Sketch.hpp"

class ExampleSketch : public Sketch {
public:
  ExampleSketch() = default;
  void Setup() override;
  void Update(float dt) override;
  void Draw() override;
  void OnEvent(const SDL_Event &e) override;
};
