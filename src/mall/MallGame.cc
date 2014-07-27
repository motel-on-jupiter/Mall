/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "MallGame.h"

#include <GL/glew.h>
#include <glm/gtx/random.hpp>

#include "util/logging/Logger.h"
#include "util/macro_util.h"

MallGame::MallGame() :
    initialized_(false),
    walker_(glm::vec2(10.0f, 10.0f)),
    goal_(nullptr) {
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

void MallGame::Update(float elapsed_time, glm::vec2 window_size) {
  UNUSED(elapsed_time);

  if (!initialized_) {
    return;
  }

  if (!walker_.HasReached()) {
    free(goal_);
    goal_ = new GoalNode(glm::linearRand(glm::vec2(), window_size));
    walker_.SetGoal(goal_);
  }
  walker_.Update();

  return;
}

int MallGame::Draw(glm::vec2 window_size) {
  if (!initialized_) {
    return 1;
  }

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  walker_.Draw(window_size);

  return 0;
}
