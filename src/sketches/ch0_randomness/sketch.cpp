#include "sketch.hpp"
#include "engine/util/Rand.hpp"
#include "sketches/ch0_randomness/entities/Walker.hpp"
#include <memory>

using namespace util;
int num_entities = 10;

void RandomnessSketch::Setup() {
  Background(50, 50, 20);
  util::random::seed();
  for (int i = 0; i < num_entities; ++i) {
    m_Entities.push_back(
        std::make_unique<Walker>(random::rand_real(0, p5().Width()),
                                 random::rand_real(0, p5().Height())));
  }
}

void RandomnessSketch::Update(float dt) {
  for (auto const &e : m_Entities) {
    e->AddX(40 * dt);
  }
}

void RandomnessSketch::Draw() {
  // Background(50, 50, 50, 20);
  p5().Fill(255, 0, 0);
  p5().Stroke(255, 0, 0);
  for (auto const &e : m_Entities) {
    e->Render(G());
  }
}

void RandomnessSketch::OnEvent(const SDL_Event &e) {}
