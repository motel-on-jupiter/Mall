/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "BridgeTrafficCase.h"

#include <vector>
#include <GL/glew.h>
#include <boost/foreach.hpp>

#include "navigation/Waypoint.h"
#include "util/logging/Logger.h"
#include "util/macro_util.h"

BridgeStage::BridgeStage() : MallStage() {

}

BridgeStage::~BridgeStage() {

}

const glm::vec2 BridgeStage::kWaypointPositionTbl[] = {
  glm::vec2(1.0f, 0.2f),
  glm::vec2(0.0f, 0.2f),
  glm::vec2(0.0f, 0.3f),
  glm::vec2(1.0f, 0.3f),
  glm::vec2(1.0f, 0.7f),
  glm::vec2(0.0f, 0.7f),
  glm::vec2(0.0f, 0.8f),
  glm::vec2(1.0f, 0.8f),
};

int BridgeStage::Initialize(const glm::vec2 &window_size) {
  for (int i=0; i<ARRAYSIZE(kWaypointPositionTbl); ++i) {
    Waypoint *point = new Waypoint(window_size * kWaypointPositionTbl[i]);
    if (point == nullptr) {
      LOGGER.Error("Failed to allocate the waypoint object (idx: %d)", i);
      graph().Clear();
      return -1;
    }
    graph().AddPoint(point);
  }
  for (int i=0; i<ARRAYSIZE(kWaypointPositionTbl) / 2; ++i) {
    graph().points()[i * 2]->AddNextPoint(graph().points()[i * 2 + 1]);
  }
  return 0;
}

void BridgeStage::Finalize() {
  graph().Clear();
}

BridgeTrafficCase::BridgeTrafficCase() :
    initialized_(false), stage_(), walkers_() {
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
  for (unsigned int i=0; i<stage_.const_graph().points().size() / 2; ++i) {
    walkers_.push_back(new Walker(stage_.const_graph(),
                                  *(stage_.const_graph().points()[i * 2]),
                                  *(stage_.const_graph().points()[i * 2 + 1])));
  }

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
  BOOST_FOREACH(Walker *walker, walkers_) {
    delete walker;
  }
  walkers_.clear();
  stage_.Finalize();
  initialized_ = false;
  return;
}

void BridgeTrafficCase::Update(float elapsed_time) {
  UNUSED(elapsed_time);
  BOOST_FOREACH(Walker *walker, walkers_) {
    walker->Update();
  }
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

  stage_.Draw(window_size);
  BOOST_FOREACH(Walker *walker, walkers_) {
    walker->Draw(window_size);
  }
  return 0;
}

int BridgeTrafficCase::OnMouseButtonDown(unsigned char button, int x, int y, glm::vec2 window_size) {
  UNUSED(button);
  UNUSED(x);
  UNUSED(y);
  UNUSED(window_size);
  return 0;
}
