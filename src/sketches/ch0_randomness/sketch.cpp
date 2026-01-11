#include "sketch.hpp"
#include "sketches/ch0_randomness/entities/Walker.hpp"
#include <memory>

void RandomnessSketch::Setup() {
  m_Entities.push_back(std::make_unique<Walker>(200.0, 200.0));
}

void RandomnessSketch::Update(float dt) {
  for (auto const &e : m_Entities) {
    e->AddX(40 * dt);
  }
}

void RandomnessSketch::Draw() {
  Background(50, 50, 50);
  p5().Fill(255, 0, 0);
  p5().Stroke(255, 0, 0);
  for (auto const &e : m_Entities) {
    e->Render(G());
  }
}

void RandomnessSketch::OnEvent(const SDL_Event &e) {}
