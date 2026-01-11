#include "engine/Canvas.hpp"
#include "sketches/ch0_randomness/sketch.hpp"
// #include "sketches/example/ExampleSketch.hpp"
#include <SDL3/SDL.h>
#include <memory>

int main() {
  WindowProps windowProps{1200, 1200, "Test Canvas", "1.0.0"};
  std::unique_ptr<Canvas> canvas = std::make_unique<Canvas>(windowProps);
  RandomnessSketch sketch;
  canvas->Run(sketch);

  return 0;
}
