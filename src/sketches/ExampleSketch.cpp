#include "sketches/ExampleSketch.hpp"
#include <SDL3/SDL.h>

void ExampleSketch::Setup() {
  // run once
}

void ExampleSketch::Update(float dt) {
  (void)dt; // silence unused warning
}

void ExampleSketch::Draw() {
  Background(255, 0, 0, 255);

  Clear();
}

void ExampleSketch::OnEvent(const SDL_Event &e) {
  if (e.type == SDL_EVENT_KEY_DOWN) {
    // handle input
  }
}
