/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "BridgeScene.h"

#include <vector>
#include <GL/glew.h>
#include <boost/foreach.hpp>

#include "core/actor/Automobile.h"
#include "core/actor/Walker.h"
#include "navigation/Waypoint.h"
#include "util/logging/Logger.h"
#include "util/macro_util.h"

BridgeStage::BridgeStage() : MallStage() {
}

BridgeStage::~BridgeStage() {
}

const glm::vec2 BridgeStage::kSidewalkWaypointPosTbl[] = {
  glm::vec2(20.0f, 3.0f),
  glm::vec2(0.0f, 3.0f),
  glm::vec2(0.0f, 4.0f),
  glm::vec2(20.0f, 4.0f),
  glm::vec2(20.0f, 11.0f),
  glm::vec2(0.0f, 11.0f),
  glm::vec2(0.0f, 12.0f),
  glm::vec2(20.0f, 12.0f),
};

const glm::vec2 BridgeStage::kRoadwayWaypointPosTbl[] = {
  glm::vec2(0.0f, 6.5f),
  glm::vec2(20.0f, 6.5f),
  glm::vec2(20.0f, 8.5f),
  glm::vec2(0.0f, 8.5f),
};

int BridgeStage::Initialize(const glm::vec2 &size) {
  // Call the base-class method
  int ret = MallStage::Initialize(size);
  if (ret != 0) {
    return ret;
  }

  // Create the way-points
  for (int i=0; i<ARRAYSIZE(kSidewalkWaypointPosTbl); ++i) {
    Waypoint *point = new Waypoint(kSidewalkWaypointPosTbl[i]);
    if (point == nullptr) {
      LOGGER.Error("Failed to allocate the sidewalk waypoint object (idx: %d)", i);
      graph().Clear();
      return -1;
    }
    graph().AddPoint(point);
  }
  for (int i=0; i<ARRAYSIZE(kSidewalkWaypointPosTbl) / 2; ++i) {
    graph().points()[i * 2]->AddNextPoint(graph().points()[i * 2 + 1]);
  }
  for (int i=0; i<ARRAYSIZE(kRoadwayWaypointPosTbl); ++i) {
    Waypoint *point = new Waypoint(kRoadwayWaypointPosTbl[i]);
    if (point == nullptr) {
      LOGGER.Error("Failed to allocate the roadway waypoint object (idx: %d)", i);
      graph().Clear();
      return -1;
    }
    graph().AddPoint(point);
  }
  for (int i=0; i<ARRAYSIZE(kRoadwayWaypointPosTbl) / 2; ++i) {
    graph().points()[ARRAYSIZE(kSidewalkWaypointPosTbl) + i * 2]->
        AddNextPoint(graph().points()[ARRAYSIZE(kSidewalkWaypointPosTbl) + i * 2 + 1]);
  }
  return 0;
}

void BridgeStage::Finalize() {
  graph().Clear();
}

BridgeScene::BridgeScene() :
    MallBaseGameScene("Bridge Traffic"),
    initialized_(false), stage_(), walkers_(), automobiles_() {
  memset(lastgenwalkers_, 0, sizeof(lastgenwalkers_));
  memset(lastgenautomobiles_, 0, sizeof(lastgenautomobiles_));
}

BridgeScene::~BridgeScene() {
  if (initialized_) {
    if (!Logger::is_destroyed()) {
      LOGGER.Warn("Need to finalize the game");
    }
  }
}

int BridgeScene::Initialize(const glm::vec2 &stage_size) {
  // Initialize the stage
  int ret = stage_.Initialize(stage_size);
  if (ret != 0) {
    LOGGER.Error("Failed to initialize the stage");
    return -1;
  }

  // Update the OpenGL flags
  glDisable(GL_LIGHTING);
  glDisable(GL_LIGHT0);

  // Update the flags
  initialized_ = true;
  return 0;
}

void BridgeScene::Finalize() {
  if (!initialized_) {
    LOGGER.Notice("Ignored the duplicate call to finalize game");
    return;
  }
  BOOST_FOREACH(Automobile *automobile, automobiles_) {
    delete automobile;
  }
  automobiles_.clear();
  BOOST_FOREACH(Walker *walker, walkers_) {
    delete walker;
  }
  walkers_.clear();
  stage_.Finalize();
  initialized_ = false;
  return;
}

int BridgeScene::Update(float elapsed_time) {
  if (!initialized_) {
    return 1;
  }

  int status = 0;

  // Generate new walker
  for (unsigned int i=0; i<4; ++i) {
    if ((lastgenwalkers_[i] != nullptr) &&
        (glm::distance(stage_.const_graph().points()[i * 2]->pos(),
                       lastgenwalkers_[i]->pos()) <=
            Walker::kScale.y * 1.0f)) {
      continue;
    }

    float rot = glm::radians((i % 2 == 0) ? -90.0f : 90.0f);
    if (glm::linearRand(0.0f, 1.0f) < 0.6f * elapsed_time) {
      Walker *walker = new Walker(rot, stage_.const_graph(),
                                  *(stage_.const_graph().points()[i * 2]),
                                  *(stage_.const_graph().points()[i * 2 + 1]));
      if (walker == nullptr) {
        LOGGER.Error("Failed to create new walker");
        status = -1;
        break;
      } else {
        walkers_.push_back(walker);
        lastgenwalkers_[i] = walker;
      }
    }
  }
  // Generate new automobile
  for (unsigned int i=4; i<6; ++i) {
    if ((lastgenautomobiles_[i - 4] != nullptr) &&
        (glm::distance(stage_.const_graph().points()[i * 2]->pos(),
                       lastgenautomobiles_[i - 4]->pos()) <=
            Automobile::kScale.y * 1.0f)) {
      continue;
    }

    float rot = glm::radians((i % 2 == 0) ? 90.0f : -90.0f);
    if (glm::linearRand(0.0f, 1.0f) < 0.45f * elapsed_time) {
      Automobile *automobile = new Automobile(rot, stage_.const_graph(),
                                              *(stage_.const_graph().points()[i * 2]),
                                              *(stage_.const_graph().points()[i * 2 + 1]));
      if (automobile == nullptr) {
        LOGGER.Error("Failed to create new automobile");
        status = -1;
        break;
      } else {
        automobiles_.push_back(automobile);
        lastgenautomobiles_[i - 4] = automobile;
      }
    }
  }

  // Update the walkers
  for(auto it = walkers_.begin(); it != walkers_.end();) {
    Walker *walker = *it;
    assert(walker != nullptr);
    walker->Update(elapsed_time);
    if (walker->HasReached() && !(walker->navi().rerouting())) {
      delete walker;
      it = walkers_.erase(it);
    } else {
      ++it;
    }
  }
  // Update the automobiles
  for(auto it = automobiles_.begin(); it != automobiles_.end();) {
    Automobile *automobile = *it;
    assert(automobile != nullptr);
    automobile->Update(elapsed_time);
    if (automobile->HasReached() && !(automobile->navi().rerouting())) {
      delete automobile;
      it = automobiles_.erase(it);
    } else {
      ++it;
    }
  }

  return status;
}

int BridgeScene::Draw() {
  if (!initialized_) {
    return 1;
  }
  stage_.Draw();
  BOOST_FOREACH(Walker *walker, walkers_) {
    walker->Draw();
  }
  BOOST_FOREACH(Automobile *automobile, automobiles_) {
    automobile->Draw();
  }
  return 0;
}

int BridgeScene::OnMouseButtonDown(unsigned char button, const glm::vec2 &cursor_pos) {
  UNUSED(button);
  UNUSED(cursor_pos);
  return 0;
}
