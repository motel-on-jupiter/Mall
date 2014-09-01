/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#ifndef SDLWRAP_H_
#define SDLWRAP_H_

#include "util/wrapper/glgraphics_wrap.h"

#define SDL_MAIN_HANDLED
#include <SDL.h>
#undef WIN32_LEAN_AND_MEAN
#include <SDL_opengl.h>

#endif /* SDLWRAP_H_ */
