#include "sketches/ExampleSketch.hpp"

void ExampleSketch::Setup() {
  // run once
  RandomSeed(100);
  PointSize(6);
}

void ExampleSketch::Update(float dt) {
  (void)dt; // silence unused warning
}

void ExampleSketch::Draw() {
  Background(25, 20, 50, 255);
  Stroke(255, 0, 0);
  StrokeWeight(20);
  Circle(Width() / 2, Height() / 2, 100);
  Rect(500, 500, 100);

  StrokeWeight(2);
  Line(0, 0, 100, 100);

  Point(200, 300);
}

void ExampleSketch::OnEvent(const SDL_Event &e) {
  if (e.type == SDL_EVENT_KEY_DOWN) {
    // handle input
  }
}
