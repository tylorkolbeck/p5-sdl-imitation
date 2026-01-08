#include "Canvas.hpp"
#include "SDL3/SDL_init.h"
#include <SDL3/SDL.h>
#include <memory>

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
bool running = true;

void SDL_AppQuit();

/* This function runs once at startup. */
void SDL_AppInit() {
  SDL_SetAppMetadata("Example Renderer Clear", "1.0",
                     "com.example.renderer-clear");

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
  }

  if (!SDL_CreateWindowAndRenderer("examples/renderer/clear", 640, 480,
                                   SDL_WINDOW_RESIZABLE, &window, &renderer)) {
    SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
  }
  SDL_SetRenderLogicalPresentation(renderer, 640, 480,
                                   SDL_LOGICAL_PRESENTATION_LETTERBOX);
}

SDL_AppResult SDL_AppEvent(SDL_Event *event) {
  if (event->type == SDL_EVENT_QUIT) {
    SDL_AppQuit();
    return SDL_APP_SUCCESS; /* end the program, reporting success to the OS. */
  }
  return SDL_APP_CONTINUE; /* carry on with the program! */
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate() {
  const double now = ((double)SDL_GetTicks()) /
                     1000.0; /* convert from milliseconds to seconds. */
  /* choose the color for the frame we will draw. The sine wave trick makes it
   * fade between colors smoothly. */
  const float red = (float)(0.5 + 0.5 * SDL_sin(now));
  const float green = (float)(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3));
  const float blue = (float)(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3));
  SDL_SetRenderDrawColorFloat(
      renderer, red, green, blue,
      SDL_ALPHA_OPAQUE_FLOAT); /* new color, full alpha. */

  /* clear the window to the draw color. */
  SDL_RenderClear(renderer);

  /* put the newly-cleared rendering on the screen. */
  SDL_RenderPresent(renderer);

  return SDL_APP_CONTINUE; /* carry on with the program! */
}

void SDL_AppQuit() {
  running = false;
  SDL_Quit();
}

// int main() {
//   SDL_AppInit();
//   while (running) {
//     SDL_Event event;
//
//     while (SDL_PollEvent(&event)) {
//       SDL_AppEvent(&event);
//     }
//     SDL_AppIterate();
//   }
//   return 0;
// }

int main() {
  WindowProps windowProps{800, 800, "Test Canvas"};
  std::unique_ptr<Canvas> canvas = std::make_unique<Canvas>(windowProps);
  canvas->Run();

  return 0;
}
