/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "MallGame.h"

#include <boost/foreach.hpp>
#include <GL/glew.h>
#include <glm/gtx/random.hpp>

#include "util/logging/Logger.h"
#include "util/macro_util.h"

const int MallGame::kNumWalkWalkers = 5;

MallGame::MallGame() :
    initialized_(false),
    stage_(),
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

  stage_.Initialize(window_size);
  for (int i=0; i<kNumWalkWalkers; ++i) {
    unsigned int originidx = static_cast<unsigned int>(glm::linearRand(0.0f, static_cast<float>(stage_.const_graph().points().size())));
    unsigned int terminusidx = static_cast<int>(glm::linearRand(0.0f, static_cast<float>(stage_.const_graph().points().size())));
    Walker *walker = new Walker(stage_.const_graph(), *(stage_.const_graph().points()[originidx]), *(stage_.const_graph().points()[terminusidx]));
    if (walker == nullptr) {
      LOGGER.Error("Failed to create the walker object (idx: %d)", i);
      BOOST_FOREACH (auto walker, walkers_) {
        delete walker;
      }
      walkers_.clear();
      return -1;
    }
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
    delete walker;
  }
  stage_.Finalize();

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
    if ((*walker).CheckStatus() == Walker::kWalkerStandBy) {
      unsigned int terminusidx = static_cast<int>(glm::linearRand(0.0f, static_cast<float>(stage_.const_graph().points().size())));
      (*walker).Reroute(*(stage_.const_graph().points()[terminusidx]));
    }
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

  stage_.Draw(window_size);
  BOOST_FOREACH (auto walker, walkers_) {
    walker->Draw(window_size);
  }

  return 0;
}

int MallGame::OnMouseButtonDown(Uint8 button, Sint32 x, Sint32 y, glm::vec2 window_size) {
  if (button == 1) {
    Sint32 maxx = static_cast<Sint32>(window_size.x) - 1;
    Sint32 maxy = static_cast<Sint32>(window_size.y) - 1;
    if (x != 0 && y != 0 && x != maxx && y != maxy) {
      const Waypoint *terminus = stage_.const_graph().CalcNearestPoint(glm::vec2(x, y));
      walkers_[0]->Reroute(*terminus);
    }
  }
  return 0;
}
