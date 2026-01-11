#include "engine/Canvas.hpp"
#include "sketches/ExampleSketch.hpp"
#include <SDL3/SDL.h>
#include <memory>

int main() {
  WindowProps windowProps{800, 800, "Test Canvas", "1.0.0"};
  std::unique_ptr<Canvas> canvas = std::make_unique<Canvas>(windowProps);
  ExampleSketch sketch;
  canvas->Run(sketch);

  return 0;
}
