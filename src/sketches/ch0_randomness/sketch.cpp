#include "sketch.hpp"
#include "engine/util/Rand.hpp"
#include "sketches/ch0_randomness/entities/Walker.hpp"
#include <memory>

using namespace util::random;

int num_entities = 1;

void RandomnessSketch::Setup() {
  Background(50, 50, 100);
  util::random::seed();
  for (int i = 0; i < num_entities; ++i) {
    auto w = std::make_unique<Walker>(
        Vec{static_cast<float>((float)Width() / 2.0),
            static_cast<float>((float)Height() / 2.0)});

    m_Entities.push_back(std::move(w));
  }
}

void KeepInBounds(Vec &pos, Vec &vel, int width, int height) {
  if (pos.x > width || pos.x < 0) {
    vel.x *= -1;
  }

  if (pos.y > height || pos.y < 0) {
    vel.y *= -1;
  }
}

void RandomnessSketch::Update(float dt) {
  for (auto const &e : m_Entities) {
    // e->AddX(40 * dt);
    e->Update(dt);
    KeepInBounds(e->Pos(), e->Vel(), p5().Width(), p5().Height());
  }
}

void RandomnessSketch::Draw() {
  Background(50, 50, 50, 20);
  // p5().Fill(255, 0, 0);
  p5().Stroke(255, 255, 255);
  for (auto const &e : m_Entities) {
    e->Render(p5());
  }
}

void RandomnessSketch::OnEvent(const SDL_Event &e) {}
