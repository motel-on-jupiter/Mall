/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "BridgeTrafficCase.h"
#include <GL/glew.h>
#include "util/logging/Logger.h"
#include "util/macro_util.h"

BridgeTrafficCase::BridgeTrafficCase() :
    initialized_(false) {
}

BridgeTrafficCase::~BridgeTrafficCase() {
  if (initialized_) {
    if (!Logger::is_destroyed()) {
      LOGGER.Warn("Need to finalize the game");
    }
  }
}

int BridgeTrafficCase::Initialize(const glm::vec2 &window_size) {
  UNUSED(window_size);

  glDisable(GL_LIGHTING);
  glDisable(GL_LIGHT0);

  initialized_ = true;
  return 0;
}

void BridgeTrafficCase::Finalize() {
  if (!initialized_) {
    LOGGER.Notice("Ignored the duplicate call to finalize game");
    return;
  }
  initialized_ = false;
  return;
}

void BridgeTrafficCase::Update(float elapsed_time) {
  UNUSED(elapsed_time);
  return;
}

int BridgeTrafficCase::Draw(glm::vec2 window_size) {
  UNUSED(window_size);

  if (!initialized_) {
    return 1;
  }

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  return 0;
}

int BridgeTrafficCase::OnMouseButtonDown(unsigned char button, int x, int y, glm::vec2 window_size) {
  UNUSED(button);
  UNUSED(x);
  UNUSED(y);
  UNUSED(window_size);
  return 0;
}
