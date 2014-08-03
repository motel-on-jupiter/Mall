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

MallGame::MallGame() :
    initialized_(false),
    nodemap_(),
    walkers_() {
}

MallGame::~MallGame() {
  if (initialized_) {
    if (!Logger::is_destroyed()) {
      LOGGER.Warn("Need to finalize the game");
    }
  }
}

int MallGame::Initialize(const glm::vec2 &window_size) {
  LOGGER.Info("Set up the game");

  nodemap_.Initialize(window_size);
  for (int i=0; i<kNumWalkWalkers; ++i) {
    unsigned int startnodeidx = static_cast<unsigned int>(glm::linearRand(0.0f, static_cast<float>(nodemap_.nodes().size())));
    NodeMapWalker *walker = new NodeMapWalker(*(nodemap_.nodes()[startnodeidx]), nodemap_);
    unsigned int goalnodeidx = static_cast<int>(glm::linearRand(0.0f, static_cast<float>(nodemap_.nodes().size())));
    walker->UpdateFinalGoal(nodemap_.nodes()[goalnodeidx]);
    walkers_.push_back(walker);
  }

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
  nodemap_.Finalize();

  initialized_ = false;

  return;
}

void MallGame::Update(float elapsed_time) {
  UNUSED(elapsed_time);

  if (!initialized_) {
    return;
  }

  BOOST_FOREACH (auto walker, walkers_) {
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

  nodemap_.Draw(window_size);
  BOOST_FOREACH (auto walker, walkers_) {
    walker->Draw(window_size);
#ifdef _DEBUG
    walker->DrawApproach(window_size);
#endif // _DEBUG
  }

  return 0;
}
