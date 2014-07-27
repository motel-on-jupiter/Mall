/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "MallGame.h"

#include <GL/glew.h>

#include "util/logging/Logger.h"
#include "util/macro_util.h"

MallGame::MallGame() : initialized_(false), rect_pos_(10.0f, 10.0f), rect_size_(20.0f, 20.0f) {
}

MallGame::~MallGame() {
  if (initialized_) {
    if (!Logger::is_destroyed()) {
      LOGGER.Warn("Need to finalize the game");
    }
  }
}

int MallGame::Initialize() {
  LOGGER.Info("Set up the game");

  glDisable(GL_LIGHTING);
  glDisable(GL_LIGHT0);

  initialized_ = true;

  return 0;
}

void MallGame::Finalize() {
  if (!initialized_) {
    LOGGER.Notice("Ignored the duplicate call to finalize game");
    return;
  }

  LOGGER.Info("Clean up the game");

  initialized_ = false;

  return;
}

void MallGame::Update(float elapsed_time) {
  UNUSED(elapsed_time);

  if (!initialized_) {
    return;
  }
  return;
}

int MallGame::Draw(glm::vec2 window_size) {
  if (!initialized_) {
    return 1;
  }

  // clear
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glBegin(GL_QUADS);
  glVertex3f(rect_pos_.x / window_size.x * 2.0f - 1.0f,
             rect_pos_.y / window_size.y * 2.0f - 1.0f, 0.0f);
  glVertex3f(rect_pos_.x / window_size.x * 2.0f - 1.0f,
             (rect_pos_.y + rect_size_.y) / window_size.y * 2.0f - 1.0f,
             0.0f);
  glVertex3f((rect_pos_.x + rect_size_.x) / window_size.x * 2.0f - 1.0f,
             (rect_pos_.y + rect_size_.y) / window_size.y * 2.0f - 1.0f,
             0.0f);
  glVertex3f((rect_pos_.x + rect_size_.x) / window_size.x * 2.0f - 1.0f,
             rect_pos_.y / window_size.y * 2.0f - 1.0f, 0.0f);
  glEnd();

  return 0;
}
