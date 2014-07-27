/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "MallMain.h"

#include <SDL.h>
#include <SDL_opengl.h>

#include "mall/MallGame.h"
#include "util/logging/Logger.h"
#include "util/macro_util.h"
#include "util/wrapper/glgraphics_wrap.h"

static const std::string kWindowCaption = "Mall - The Motel On Jupiter";
static const Uint32 kWindowWidth = 640;
static const Uint32 kWindowHeight = 480;
static const Uint32 kFPS = 60;

static const Uint32 kGameLoopInterval = 1000 / kFPS;

static SDL_Window *window = nullptr;
static SDL_GLContext context = nullptr;
static MallGame game;
static Uint32 next_time = 0;

static void MallCleanUp();

int MallMain(int argc, char *argv[], const char *config_path) {
  UNUSED(argc);
  UNUSED(argv);
  UNUSED(config_path);

  LOGGER.Info("Set up the application");

  // initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    LOGGER.Error("Failed to initialize SDL video system (errmsg: %s)", SDL_GetError());
    return -1;
  }

  // enable double buffering
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  // create window
  window = SDL_CreateWindow(kWindowCaption.c_str(), SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, kWindowWidth, kWindowHeight,
                            SDL_WINDOW_OPENGL);
  if (window == nullptr) {
    LOGGER.Error("Failed to create SDL window (errmsg: %s)", SDL_GetError());
    MallCleanUp();
    return -1;
  }

  // create OpenGL context
  context = SDL_GL_CreateContext(window);
  if (context == nullptr) {
    LOGGER.Error("Failed to create SDL context for OpenGL (errmsg: %s)", SDL_GetError());
    MallCleanUp();
    return -1;
  }

  int ret = game.Initialize();
  if (ret < 0) {
    LOGGER.Error("Failed to initialize the game (ret: %d)", ret);
    MallCleanUp();
    return -1;
  }

  // mainloop
  next_time = SDL_GetTicks() + kGameLoopInterval;
  bool skip_draw = false;
  int loop_stat = 0;
  while (true) {
    // check event
    bool escape_loop = false;
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          escape_loop = true;
          break;
        case SDL_KEYDOWN:
          if (event.key.keysym.sym == SDLK_ESCAPE) {
            escape_loop = true;
            break;
          }
          break;
      }
    }
    if (escape_loop) {
      break;
    }

    // update and draw
    if (!skip_draw) {
      ret = game.Draw(glm::vec2(kWindowWidth, kWindowHeight));
      if (ret < 0) {
        LOGGER.Error("Failed to draw the game objects (ret: %d)", ret);
        loop_stat = -1;
        break;
      }
      SDL_GL_SwapWindow(window);
    }

    int delay_time = static_cast<int>(next_time - SDL_GetTicks());
    if (delay_time > 0) {
      SDL_Delay(static_cast<Uint32>(delay_time));
      skip_draw = false;
    } else {
      // skip next draw step because of no time
      skip_draw = true;
    }
    next_time += kGameLoopInterval;
  }

  MallCleanUp();
  return loop_stat;
}

static void MallCleanUp() {
  LOGGER.Info("Clean up the application");

  game.Finalize();
  if (context != nullptr) {
    SDL_GL_DeleteContext(context);
  }
  if (window != nullptr) {
    SDL_DestroyWindow(window);
  }
  SDL_Quit();
}
