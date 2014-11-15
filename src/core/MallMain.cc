/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "MallMain.h"

#include <algorithm>
#include <sstream>
#include <mmsystem.h>

#include <SDL.h>
#include <SDL_opengl.h>

#include "core/MallGame.h"
#include "core/MallTweakerContext.h"
#include "mojgame/auxiliary/atb_aux.h"
#include "mojgame/auxiliary/csyntax_aux.h"
#include "mojgame/includer/gl_include.h"
#include "mojgame/logging/Logger.h"
#include "mojgame/misc/FPSCounter.h"

static const std::string kWindowCaption = "Mall - The Motel on Jupiter";
static const Uint32 kWindowWidth = 800;
static const Uint32 kWindowHeight = 600;
static const Uint32 kIdealFrameRate = 60;
static const glm::vec2 kStageSize = glm::vec2(20, 15);

static const int kGameLoopInterval = 1000 / kIdealFrameRate;
static const float kGameLoopIntervalSec = 1.0f / kIdealFrameRate;
static const int kFPSCountSamplingTime = 1000;

static SDL_Window *window = nullptr;
static SDL_GLContext context = nullptr;
static TwBar *tw_bar = nullptr;
static MallGame game;
static mojgame::FPSCounter fps_counter(kFPSCountSamplingTime);

static void MallCleanUp();

int MallMain(int argc, char *argv[], const char *config_path) {
  UNUSED(argc);
  UNUSED(argv);
  UNUSED(config_path);

  mojgame::LOGGER().Info("Set up the application");

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    mojgame::LOGGER().Error("Failed to initialize SDL video system (errmsg: %s)", SDL_GetError());
    return -1;
  }

  // Enable double buffering
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  // Create the window
  window = SDL_CreateWindow(kWindowCaption.c_str(), SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, kWindowWidth, kWindowHeight,
                            SDL_WINDOW_OPENGL);
  if (window == nullptr) {
    mojgame::LOGGER().Error("Failed to create SDL window (errmsg: %s)", SDL_GetError());
    MallCleanUp();
    return -1;
  }

  // Create OpenGL context
  context = SDL_GL_CreateContext(window);
  if (context == nullptr) {
    mojgame::LOGGER().Error("Failed to create SDL context for OpenGL (errmsg: %s)", SDL_GetError());
    MallCleanUp();
    return -1;
  }

  // Initialize the GLUT (for bitmap font support)
  int glut_argc = 0;
  glutInit(&glut_argc, {});

  // Initialize the tweaker library
  if (TwInit(TW_OPENGL, NULL) == 0) {
    mojgame::LOGGER().Error("Failed to initialize the tweaker library (errmsg: %s)", TwGetLastError());
    MallCleanUp();
    return -1;
  }
  if (TwWindowSize(kWindowWidth, kWindowHeight) == 0) {
    mojgame::LOGGER().Error("Failed to set the window size to tweaker (errmsg: %s)", TwGetLastError());
    MallCleanUp();
    return -1;
  }
  tw_bar = TwNewBar("TweakMenu");
  std::stringstream tw_def;
  tw_def << "TweakMenu position='" << 550 << " " << 10 <<
      "' size='" << 240 << " " << 580 << "' color='41 126 231' iconified=true";
  TwDefine(tw_def.str().c_str());
  if (TwAddVarRO(tw_bar, "SYSTEM_ACTUAL_FRAME_RATE", TW_TYPE_INT8,
                 &(tweaker_ctx.system_actual_fps),
                 "group='System' label='Actual Frame Rate'") == 0) {
    mojgame::LOGGER().Warn("Failed to add a tweak variable for actual-FPS (errmsg: %s)", TwGetLastError());
  }
  if (TwAddVarRW(tw_bar, "SYSTEM_TIME_SPEED", TW_TYPE_FLOAT,
                 &(tweaker_ctx.system_time_speed),
                 "group='System' label='Time Speed' min='0' max='30' step='0.5'") == 0) {
    mojgame::LOGGER().Warn("Failed to add a tweak variable for time-speed (errmsg: %s)", TwGetLastError());
  }
  if (TwAddVarRW(tw_bar, "WAKLER_ROUTE_VISIBLE", TW_TYPE_BOOLCPP,
                 &(tweaker_ctx.walker_route_visible),
                 "group='Walker' label='Route Visible'") == 0) {
    mojgame::LOGGER().Warn("Failed to add a tweak variable for route-visible (errmsg: %s)", TwGetLastError());
  }
  if (TwAddVarRW(tw_bar, "STAGE_WAYPOINT_VISIBLE", TW_TYPE_BOOLCPP,
                 &(tweaker_ctx.stage_waypoint_visible),
                 "group='Stage' label='Waypoint Visible'") == 0) {
    mojgame::LOGGER().Warn("Failed to add a tweak variable for waypoint-visible (errmsg: %s)", TwGetLastError());
  }
  if (TwAddVarRW(tw_bar, "STAGE_TRACABLE_VISIBLE", TW_TYPE_BOOLCPP,
                 &(tweaker_ctx.stage_traceable_visible),
                 "group='Stage' label='Traceable Visible'") == 0) {
    mojgame::LOGGER().Warn("Failed to add a tweak variable for graph-traceable-visible (errmsg: %s)", TwGetLastError());
  }

  // Initialize the game
  if (game.Initialize(kStageSize) != 0) {
    mojgame::LOGGER().Error("Failed to initialize the game objects");
    MallCleanUp();
    return -1;
  }

  // Set the minimum timer resolution
  timeBeginPeriod(1);

  // Execute the mainloop
  int loop_stat = 0;
  while (true) {
    int start_tick = SDL_GetTicks();

    // check event
    bool escape_loop = false;
    SDL_Event event;
    while (SDL_PollEvent(&event) == 1) {
      if (mojgame::atb_aux::TwEventSDL20(&event) != 0) {
        continue;
      }
      switch (event.type) {
        case SDL_QUIT:
          escape_loop = true;
          break;
        case SDL_KEYDOWN:
          game.OnKeyboardDown(event.key.keysym.sym);
          break;
        case SDL_MOUSEBUTTONDOWN:
          game.OnMouseButtonDown(event.button.button, event.button.x, event.button.y,
                                 glm::vec2(kWindowWidth, kWindowHeight));
          break;
      }
    }
    if (escape_loop || !game.ongoing()) {
      break;
    }

    // Update the game
    int ret = game.Update(kGameLoopIntervalSec * tweaker_ctx.system_time_speed);
    if (ret < 0) {
      mojgame::LOGGER().Error("Failed to update the game objects (ret: %d)", ret);
      loop_stat = -1;
      break;
    }

    // Draw the objects
    ret = game.Draw(glm::vec2(kWindowWidth, kWindowHeight));
    if (ret < 0) {
      mojgame::LOGGER().Error("Failed to draw the game objects (ret: %d)", ret);
      loop_stat = -1;
      break;
    }
    if (TwDraw() == 0) {
      mojgame::LOGGER().Error("Failed to draw the tweaker (errmsg: %s)", TwGetLastError());
      loop_stat = -1;
      break;
    }
    SDL_GL_SwapWindow(window);

    int finish_tick = SDL_GetTicks();
    int exec_tick = finish_tick - start_tick;
    Sleep(std::max<int>(kGameLoopInterval - exec_tick, 1));

    fps_counter.Update(SDL_GetTicks());
    tweaker_ctx.system_actual_fps = fps_counter.fps();
  }

  // Reset the minimum timer resolution
  timeEndPeriod(1);

  MallCleanUp();
  return loop_stat;
}

static void MallCleanUp() {
  mojgame::LOGGER().Info("Clean up the application");

  game.Finalize();
  if (TwRemoveAllVars(tw_bar) == 0) {
    mojgame::LOGGER().Warn("Failed to remove all tweaker varibables (errmsg: %s)",
                TwGetLastError());
  }
  if (TwTerminate() == 0) {
    // Ignore the error to terminate the tweaker
    // because the tweaker library may be not initialized
  }
  if (context != nullptr) {
    SDL_GL_DeleteContext(context);
  }
  if (window != nullptr) {
    SDL_DestroyWindow(window);
  }
  SDL_Quit();
}