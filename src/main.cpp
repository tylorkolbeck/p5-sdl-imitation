#include "Canvas.hpp"
#include <SDL3/SDL.h>
#include <memory>

int main() {
  WindowProps windowProps{800, 800, "Test Canvas"};
  std::unique_ptr<Canvas> canvas = std::make_unique<Canvas>(windowProps);
  canvas->Run();

  return 0;
}
