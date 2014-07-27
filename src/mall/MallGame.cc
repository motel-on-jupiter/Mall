/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "MallGame.h"

#include <boost/foreach.hpp>
#include <GL/glew.h>
#include <glm/gtx/random.hpp>

#include "util/logging/Logger.h"
#include "util/macro_util.h"

const int MallGame::kNumWalkWalkers = 1;

MallGame::MallGame(const glm::vec2 &window_size) :
    initialized_(false),
    walkers_() {
  for (int i=0; i<kNumWalkWalkers; ++i) {
    WalkNode node(glm::linearRand(glm::vec2(), window_size));
    walkers_.push_back(new NodeWalker(node));
  }
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

  BOOST_FOREACH (auto walker, walkers_) {
    delete(walker);
  }

  initialized_ = false;

  return;
}

void MallGame::Update(float elapsed_time, glm::vec2 window_size) {
  UNUSED(elapsed_time);

  if (!initialized_) {
    return;
  }

  BOOST_FOREACH (auto walker, walkers_) {
    if ((*walker).HasReached()) {
      (*walker).SetGoal(new WalkNode(glm::linearRand(glm::vec2(), window_size)));
    }
    (*walker).Update();
  }

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

  BOOST_FOREACH (auto walker, walkers_) {
    walker->Draw(window_size);
#ifdef _DEBUG
    walker->DebugDraw(window_size);
#endif // _DEBUG
  }

  return 0;
}
