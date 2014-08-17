/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "ConvenienceStoreScene.h"

#include <vector>
#include <GL/glew.h>
#include <boost/foreach.hpp>

#include "mall/prop/AutomaticDoor.h"
#include "navigation/Waypoint.h"
#include "util/def/ColorDef.h"
#include "util/logging/Logger.h"
#include "util/macro_util.h"

ConvenienceStoreAttendant::ConvenienceStoreAttendant(const glm::vec2 &pos) :
  MallHuman(pos, 0.0f) {
}

void ConvenienceStoreAttendant::Draw() {
  glColor3ubv(X11Color::kOrange);
  MallHuman::Draw();
}

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
    initialized_(false), stage_(), autodoor_(nullptr), attendants_(), walkers_() {
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

  AutomaticDoor *autodoor = new AutomaticDoor(glm::vec2(7.0f, 9.0f), glm::radians(90.0f));
  if (autodoor == nullptr) {
    LOGGER.Error("Failed to create auto door");
    return -1;
  }
  autodoor_ = autodoor;

  ConvenienceStoreAttendant *attendant =
      new ConvenienceStoreAttendant(glm::vec2(10.0f, 10.0f));
  if (attendant == nullptr) {
    LOGGER.Error("Failed to create 1st attendant");
    return -1;
  }
  attendants_.push_back(attendant);
  attendant = new ConvenienceStoreAttendant(glm::vec2(12.0f, 10.0f));
  if (attendant == nullptr) {
    LOGGER.Error("Failed to create 2nd attendant");
    return -1;
  }
  attendants_.push_back(attendant);

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
  BOOST_FOREACH(auto attendant, attendants_) {
    delete attendant;
  }
  attendants_.clear();
  BOOST_FOREACH(auto walker, walkers_) {
    delete walker;
  }
  walkers_.clear();
  delete autodoor_;
  autodoor_ = nullptr;
  stage_.Finalize();
  initialized_ = false;
  return;
}

int ConvenienceStoreScene::Update(float elapsed_time) {
  UNUSED(elapsed_time);

  if (!initialized_) {
    return 1;
  }

  // Generate a walker randomly
  if (glm::linearRand(0.0f, 100.0f) < 0.5f) {
    Walker *walker = new Walker(glm::radians(90.0f), stage_.const_graph(),
                                *(stage_.const_graph().points()[4]),
                                *(stage_.const_graph().points()[3]));
    if (walker == nullptr) {
      LOGGER.Error("Failed to create a walker");
      return -1;
    }
    walkers_.push_back(walker);
  }

  // Update the objects
  autodoor_->Update(elapsed_time,
                    const_cast<const BaseEntity **>(
                        reinterpret_cast<BaseEntity **>(walkers_.data())
                        ),
                    walkers_.size());
  BOOST_FOREACH(auto attendant, attendants_) {
    attendant->Update(elapsed_time);
  }
  for (auto it = walkers_.begin(); it != walkers_.end() ; ++it) {
    Walker *walker = *it;
    walker->Update(elapsed_time);
    if (walker->HasReached() && !(walker->navi().rerouting())) {
      if (walker->lastgoal() == stage_.const_graph().points()[4]) {
        delete walker;
        it = walkers_.erase(it);
      }
      else if (walker->lastgoal() == stage_.const_graph().points()[3]) {
        walker->Reroute(*(stage_.const_graph().points()[6]));
      }
      else {
        walker->Reroute(*(stage_.const_graph().points()[4]));
      }
    }
  }
  return 0;
}

int ConvenienceStoreScene::Draw() {
  if (!initialized_) {
    return 1;
  }
  stage_.Draw();
  glColor3ubv(WebColor::kGray);
  autodoor_->Draw();
  BOOST_FOREACH(auto attendant, attendants_) {
    attendant->Draw();
  }
  BOOST_FOREACH(auto walker, walkers_) {
    walker->Draw();
  }
  return 0;
}

int ConvenienceStoreScene::OnMouseButtonDown(unsigned char button, const glm::vec2 &cursor_pos) {
  UNUSED(button);
  UNUSED(cursor_pos);
  return 0;
}
