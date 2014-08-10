/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#ifndef GLGRAPHICSWRAP_H_
#define GLGRAPHICSWRAP_H_

#include <GL/glew.h>
#include <GL/freeglut.h>

/**
 * To vanish the output of method-unused warning
 */
namespace freeglut_avoid_warning {
class _dummy {
  _dummy() {
    glutInit(nullptr, nullptr);
    glutCreateWindow(nullptr);
    glutCreateMenu(nullptr);
  }
};
}

#define SDL_MAIN_HANDLED
#include <SDL.h>
#undef WIN32_LEAN_AND_MEAN
#include <SDL_opengl.h>

#include <SDL_ttf.h>
#include "util/wrapper/glm_wrap.h"
extern int RenderTTFText(TTF_Font *Font, const SDL_Color& Color,
                         const glm::vec2 &Position, const char *Text);

#endif /* GLGRAPHICSWRAP_H_ */
