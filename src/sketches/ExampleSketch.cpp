#include "sketches/ExampleSketch.hpp"

void ExampleSketch::Setup() {
  // run once
  RandomSeed(100);
}

void ExampleSketch::Update(float dt) {
  (void)dt; // silence unused warning
}

void ExampleSketch::Draw() {
  Background(25, 20, 50, 255);
  Stroke(255, 255, 0, 255);
  Circle(Width() / 2, Height() / 2, 100);
  Stroke(255, 0, 0);
  Rect(500, 500, 100);
  Line(0, 0, 100, 100);
}

void ExampleSketch::OnEvent(const SDL_Event &e) {
  if (e.type == SDL_EVENT_KEY_DOWN) {
    // handle input
  }
}
