#include "Canvas.hpp"
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_keycode.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_timer.h"
#include "Sketch.hpp"
#include <SDL3/SDL.h>
#include <iostream>

Canvas::Canvas(const WindowProps &props)
    : m_Width(props.Width), m_Height(props.Height), m_Title(props.Title) {}

Canvas::~Canvas() {
  std::cout << "removing canvas resources" << std::endl;
  if (m_Renderer)
    SDL_DestroyRenderer(m_Renderer);
  if (m_Window)
    SDL_DestroyWindow(m_Window);
}

bool Canvas::Run(Sketch &sketch) {
  if (!Init()) {
    return 1;
  }

  Graphics graphics(m_Renderer);
  // Initialize graphics render size
  graphics.SetSize(m_Width, m_Height);

  sketch.m_Graphics = &graphics;

  sketch.Setup();

  bool running = true;
  Uint64 last = SDL_GetTicksNS();

  while (running) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_EVENT_KEY_DOWN) {
        switch (e.key.key) {
        case (SDLK_ESCAPE):
          running = false;
          break;
        }
      }
      if (e.type == SDL_EVENT_QUIT) {
        running = false;
        SDL_Quit();
      }
      if (e.type == SDL_EVENT_WINDOW_RESIZED) {
        SDL_GetCurrentRenderOutputSize(m_Renderer, &m_Width, &m_Height);
        graphics.SetSize(m_Width, m_Height);
      }
      sketch.OnEvent(e);
    }

    Uint64 now = SDL_GetTicksNS();
    float dt = (now - last) / 1'000'000'000.0f;
    last = now;

    sketch.Update(dt);
    sketch.Draw();
    SDL_RenderPresent(m_Renderer);
  }

  sketch.m_Graphics = nullptr;

  return 0;
}

bool Canvas::Init() {
  SDL_SetAppMetadata(m_Title, m_AppVersion, m_Title);
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Could not initialize SDL: %s", SDL_GetError());
    return false;
  }

  if (!SDL_CreateWindowAndRenderer(m_Title, m_Width, m_Height,
                                   SDL_WINDOW_RESIZABLE, &m_Window,
                                   &m_Renderer)) {
    SDL_Log("Could not create window/renderer: %s", SDL_GetError());
    return false;
  }

  SDL_SetRenderDrawBlendMode(m_Renderer, SDL_BLENDMODE_BLEND);
  SDL_GetCurrentRenderOutputSize(m_Renderer, &m_Width, &m_Height);

  return true;
}
