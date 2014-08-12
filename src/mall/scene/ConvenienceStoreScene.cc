/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "ConvenienceStoreScene.h"

#include <vector>
#include <GL/glew.h>
#include <boost/foreach.hpp>

#include "navigation/Waypoint.h"
#include "util/logging/Logger.h"
#include "util/macro_util.h"

ConvenienceStoreStage::ConvenienceStoreStage() : MallStage() {
}

ConvenienceStoreStage::~ConvenienceStoreStage() {

}

const glm::vec2 ConvenienceStoreStage::kWaypointPositionTbl[] = {
  glm::vec2(8.0f, 5.0f),
  glm::vec2(10.0f, 5.0f),
  glm::vec2(12.0f, 5.0f),
  glm::vec2(14.0f, 5.0f),
  glm::vec2(6.0f, 9.0f),
  glm::vec2(8.0f, 9.0f),
  glm::vec2(10.0f, 9.0f),
  glm::vec2(12.0f, 9.0f),
  glm::vec2(14.0f, 9.0f),
};

int ConvenienceStoreStage::Initialize(const glm::vec2 &size) {
  // Call the base-class method
  int ret = MallStage::Initialize(size);
  if (ret != 0) {
    return ret;
  }

  // Create the way-points
  for (int i=0; i<ARRAYSIZE(kWaypointPositionTbl); ++i) {
    Waypoint *point = new Waypoint(kWaypointPositionTbl[i]);
    if (point == nullptr) {
      LOGGER.Error("Failed to allocate the waypoint object (idx: %d)", i);
      graph().Clear();
      return -1;
    }
    graph().AddPoint(point);
  }
  graph().points()[0]->AddNextPoint(graph().points()[1]);
  graph().points()[0]->AddNextPoint(graph().points()[5]);
  graph().points()[1]->AddNextPoint(graph().points()[0]);
  graph().points()[1]->AddNextPoint(graph().points()[2]);
  graph().points()[1]->AddNextPoint(graph().points()[6]);
  graph().points()[2]->AddNextPoint(graph().points()[1]);
  graph().points()[2]->AddNextPoint(graph().points()[3]);
  graph().points()[3]->AddNextPoint(graph().points()[2]);
  graph().points()[2]->AddNextPoint(graph().points()[7]);
  graph().points()[3]->AddNextPoint(graph().points()[8]);
  graph().points()[4]->AddNextPoint(graph().points()[5]);
  graph().points()[5]->AddNextPoint(graph().points()[0]);
  graph().points()[5]->AddNextPoint(graph().points()[4]);
  graph().points()[5]->AddNextPoint(graph().points()[6]);
  graph().points()[6]->AddNextPoint(graph().points()[1]);
  graph().points()[6]->AddNextPoint(graph().points()[5]);
  graph().points()[6]->AddNextPoint(graph().points()[7]);
  graph().points()[7]->AddNextPoint(graph().points()[2]);
  graph().points()[7]->AddNextPoint(graph().points()[6]);
  graph().points()[7]->AddNextPoint(graph().points()[8]);
  graph().points()[8]->AddNextPoint(graph().points()[3]);
  graph().points()[8]->AddNextPoint(graph().points()[7]);
  return 0;
}

void ConvenienceStoreStage::Finalize() {
  graph().Clear();
}

ConvenienceStoreScene::ConvenienceStoreScene() :
    initialized_(false), stage_(), walker_(nullptr) {
}

ConvenienceStoreScene::~ConvenienceStoreScene() {
  if (initialized_) {
    if (!Logger::is_destroyed()) {
      LOGGER.Warn("Need to finalize the game");
    }
  }
}

int ConvenienceStoreScene::Initialize(const glm::vec2 &stage_size) {
  // Initialize the stage
  int ret = stage_.Initialize(stage_size);
  if (ret != 0) {
    LOGGER.Error("Failed to initialize the stage");
    return -1;
  }

  walker_ = new Walker(stage_.const_graph(),
                       *(stage_.const_graph().points()[4]),
                       *(stage_.const_graph().points()[3]));
  if (walker_ == nullptr) {
    LOGGER.Error("Failed to initialize the walker");
    return -1;
  }

  // Update the OpenGL flags
  glDisable(GL_LIGHTING);
  glDisable(GL_LIGHT0);

  // Update the flags
  initialized_ = true;
  return 0;
}

void ConvenienceStoreScene::Finalize() {
  if (!initialized_) {
    LOGGER.Notice("Ignored the duplicate call to finalize game");
    return;
  }
  delete walker_;
  walker_ = nullptr;
  stage_.Finalize();
  initialized_ = false;
  return;
}

int ConvenienceStoreScene::Update(float elapsed_time) {
  UNUSED(elapsed_time);

  if (!initialized_) {
    return 1;
  }
  walker_->Update(elapsed_time);
  if (walker_->CheckStatus() == Walker::kWalkerStandBy) {
    if (walker_->navi().GetTerminus() == stage_.const_graph().points()[4]) {
      walker_->Reroute(*(stage_.const_graph().points()[3]));
    } else if (walker_->navi().GetTerminus() == stage_.const_graph().points()[3]) {
      walker_->Reroute(*(stage_.const_graph().points()[6]));
    } else {
      walker_->Reroute(*(stage_.const_graph().points()[4]));
    }
  }
  return 0;
}

int ConvenienceStoreScene::Draw() {
  if (!initialized_) {
    return 1;
  }
  stage_.Draw();
  walker_->Draw();
  return 0;
}

int ConvenienceStoreScene::OnMouseButtonDown(unsigned char button, const glm::vec2 &cursor_pos) {
  UNUSED(button);
  UNUSED(cursor_pos);
  return 0;
}
