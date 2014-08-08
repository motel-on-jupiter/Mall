/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "MallGame.h"

#include <boost/foreach.hpp>
#include <GL/glew.h>
#include <glm/gtx/random.hpp>

#include "util/logging/Logger.h"
#include "util/macro_util.h"

const int GridWalkingCase::kNumWalkWalkers = 5;

GridWalkingCase::GridWalkingCase() :
    initialized_(false),
    stage_(),
    walkers_() {
}

GridWalkingCase::~GridWalkingCase() {
  if (initialized_) {
    if (!Logger::is_destroyed()) {
      LOGGER.Warn("Need to finalize the game");
    }
  }
}

int GridWalkingCase::Initialize(const glm::vec2 &window_size) {
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

void GridWalkingCase::Finalize() {
  if (!initialized_) {
    LOGGER.Notice("Ignored the duplicate call to finalize game");
    return;
  }

  BOOST_FOREACH (auto walker, walkers_) {
    delete walker;
  }
  stage_.Finalize();

  initialized_ = false;

  return;
}

void GridWalkingCase::Update(float elapsed_time) {
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

int GridWalkingCase::Draw(glm::vec2 window_size) {
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

int GridWalkingCase::OnMouseButtonDown(unsigned char button, int x, int y, glm::vec2 window_size) {
  UNUSED(window_size);

  if (button == 1) {
#if 0
    int maxx = static_cast<int>(window_size.x) - 1;
    int maxy = static_cast<int>(window_size.y) - 1;
    if (x != 0 && y != 0 && x != maxx && y != maxy) {
      const Waypoint *terminus = stage_.const_graph().CalcNearestPoint(glm::vec2(x, y));
      walkers_[0]->Reroute(*terminus);
    }
#endif
    Walker *nearest_walker = nullptr;
    float nearest_dist = 0.0f;
    BOOST_FOREACH (auto walker, walkers_) {
      float dist = glm::length(glm::vec2(x, y) - walker->pos());
      if ((nearest_walker == nullptr) || (dist < nearest_dist)) {
        nearest_walker = walker;
        nearest_dist = dist;
      }
    }
    if (nearest_dist < 10.0f) {
      LOGGER.Info("name: %s, sex: %d, age: %d, height: %d, weight: %d",
                  nearest_walker->property().name(),
                  nearest_walker->property().sex(),
                  nearest_walker->property().age(),
                  nearest_walker->property().height(),
                  nearest_walker->property().weight());
    }
  }
  return 0;
}

BridgeTrafficCase::BridgeTrafficCase() :
    initialized_(false),
    stage_() {
}

BridgeTrafficCase::~BridgeTrafficCase() {
  if (initialized_) {
    if (!Logger::is_destroyed()) {
      LOGGER.Warn("Need to finalize the game");
    }
  }
}

int BridgeTrafficCase::Initialize(const glm::vec2 &window_size) {
  stage_.Initialize(window_size);

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
  stage_.Finalize();
  initialized_ = false;
  return;
}

void BridgeTrafficCase::Update(float elapsed_time) {
  UNUSED(elapsed_time);
  return;
}

int BridgeTrafficCase::Draw(glm::vec2 window_size) {
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
  return 0;
}

int BridgeTrafficCase::OnMouseButtonDown(unsigned char button, int x, int y, glm::vec2 window_size) {
  UNUSED(button);
  UNUSED(x);
  UNUSED(y);
  UNUSED(window_size);
  return 0;
}

MallGame::MallGame() :
  gamecase_(nullptr) {
}

MallGame::~MallGame() {
  Finalize();
}

void MallGame::Initialize() {
}

void MallGame::Finalize() {
  if (gamecase_ == nullptr) {
    return;
  }
  gamecase_->Finalize();
  delete gamecase_;
  gamecase_ = nullptr;
}

void MallGame::Update(float elapsed_time) {
  if (gamecase_ == nullptr) {
    return;
  }
  gamecase_->Update(elapsed_time);
}

int MallGame::Draw(glm::vec2 window_size) {
  if (gamecase_ == nullptr) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    return 0;
  }
  return gamecase_->Draw(window_size);
}

int MallGame::OnKeyboardDown(SDL_Keycode key, glm::vec2 window_size) {
  if ((gamecase_ == nullptr) &&
      ((key == SDLK_1) || (key == SDLK_2))) {
    LOGGER.Info("Set up the game case");
    if (key == SDLK_1) {
      gamecase_ = new GridWalkingCase();
    } else {
      gamecase_ = new BridgeTrafficCase();
    }
    int ret = gamecase_->Initialize(window_size);
    if (ret < 0) {
      LOGGER.Error("Failed to initialize the game case");
      return -1;
    }
  }
  if ((gamecase_ != nullptr) && (key == SDLK_0)) {
    LOGGER.Info("Clean up the game-case");
    gamecase_->Finalize();
    delete gamecase_;
    gamecase_ = nullptr;
  }
  return 0;
}

int MallGame::OnMouseButtonDown(unsigned char button, int x, int y, glm::vec2 window_size) {
  if (gamecase_ != nullptr) {
    return gamecase_->OnMouseButtonDown(button, x, y, window_size);
  }
  return 0;
}
