/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "core/scene/GridScene.h"
#include "core/actor/Walker.h"
#include "mojgame/auxiliary/csyntax_aux.h"
#include "mojgame/includer/gl_include.h"
#include "mojgame/includer/glm_include.h"
#include "mojgame/logging/Logger.h"

const int GridScene::kNumWalkWalkers = 5;

const float GridStage::kGridInterval = 2.0f;

GridStage::GridStage() : MallStage() {
}

GridStage::~GridStage() {
}

int GridStage::Initialize(const glm::vec2 &size) {
  // Call the base-class method
  int ret = MallStage::Initialize(size);
  if (ret != 0) {
    return ret;
  }

  // Create the way-points
  int max_raw = static_cast<int>(size.x / kGridInterval);
  int max_column = static_cast<int>(size.y / kGridInterval);
  for (int raw = 0; raw < max_raw; ++raw) {
    for (int column = 0; column < max_column; ++column) {
      mojgame::Waypoint *point = new mojgame::Waypoint(glm::vec2(kGridInterval * (static_cast<float>(raw) + 0.5f),
                                               kGridInterval * (static_cast<float>(column) + 0.5f)));
      if (point == nullptr) {
        mojgame::LOGGER().Error("Failed to allocate the waypoint object");
        return -1;
      }

      if (raw != 0) {
        point->AddNextPoint(const_graph().points()[(raw - 1) * max_column + column]);
        graph().points()[(raw - 1) * max_column + column]->AddNextPoint(point);
      }
      if (column != 0) {
        point->AddNextPoint(const_graph().points()[raw * max_column + (column - 1)]);
        graph().points()[raw * max_column + (column - 1)]->AddNextPoint(point);
      }

      graph().AddPoint(point);
    }
  }
  return 0;
}

void GridStage::Finalize() {
  graph().Clear();
}

RoughGridStage::RoughGridStage() : GridStage() {
}

RoughGridStage::~RoughGridStage() {
}

int RoughGridStage::Initialize(const glm::vec2 &size) {
  int ret = GridStage::Initialize(size);
  if (ret != 0) {
    return ret;
  }
  for (auto it = graph().points().begin();
       it != graph().points().end();
       ++it) {
    (*it)->RemoveNextPoint((*it)->nextpoints()[rand() % (*it)->nextpoints().size()]);
  }
  return 0;
}

GridScene::GridScene() :
    MallBaseGameScene("Grid Wandering"),
    initialized_(false),
    stage_(),
    walkers_() {
}

GridScene::~GridScene() {
}

int GridScene::Initialize(const glm::vec2 &stage_size) {
  // Initialize the stage
  int ret = stage_.Initialize(stage_size);
  if (ret != 0) {
    mojgame::LOGGER().Error("Failed to initialize the stage");
    return -1;
  }

  // Create the walkers
  for (int i=0; i<kNumWalkWalkers; ++i) {
    unsigned int originidx = rand() % stage_.const_graph().points().size();
    unsigned int terminusidx = rand() % stage_.const_graph().points().size();
    Walker *walker = new Walker(0.0f, stage_.const_graph(),
                                *(stage_.const_graph().points()[originidx]),
                                *(stage_.const_graph().points()[terminusidx]));
    if (walker == nullptr) {
      mojgame::LOGGER().Error("Failed to create the walker object (idx: %d)", i);
      for (auto it = walkers_.begin(); it != walkers_.end(); ++it) {
        delete *it;
      }
      walkers_.clear();
      return -1;
    }
    walkers_.push_back(walker);
  }

  // Update the OpenGL flags
  glDisable(GL_LIGHTING);
  glDisable(GL_LIGHT0);

  // Update the flag
  initialized_ = true;
  return 0;
}

void GridScene::Finalize() {
  if (!initialized_) {
    mojgame::LOGGER().Notice("Ignored the duplicate call to finalize game");
    return;
  }
  for (auto it = walkers_.begin(); it != walkers_.end(); ++it) {
    delete *it;
  }
  stage_.Finalize();
  initialized_ = false;
  return;
}

int GridScene::Update(float elapsed_time) {
  UNUSED(elapsed_time);

  if (!initialized_) {
    return 1;
  }

  for (auto it = walkers_.begin(); it != walkers_.end(); ++it) {
    Walker *walker = *it;
    walker->Update(elapsed_time);
    if (walker->HasReached() && !(walker->navi().rerouting())) {
      unsigned int terminusidx = static_cast<int>(glm::linearRand(0.0f, static_cast<float>(stage_.const_graph().points().size())));
      walker->Reroute(*(stage_.const_graph().points()[terminusidx]));
    }
  }

  return 0;
}

int GridScene::Draw() {
  if (!initialized_) {
    return 1;
  }
  stage_.Draw();
  for (auto it = walkers_.begin(); it != walkers_.end(); ++it) {
    (*it)->Draw();
  }
  return 0;
}

int GridScene::OnMouseButtonDown(unsigned char button, const glm::vec2 &cursor_pos) {
  if (button == 1) {
    Walker *nearest_walker = nullptr;
    float nearest_dist = 0.0f;
    for (auto it = walkers_.begin(); it != walkers_.end(); ++it) {
      float dist = glm::length(cursor_pos * stage_.size() - (*it)->pos());
      if ((nearest_walker == nullptr) || (dist < nearest_dist)) {
        nearest_walker = *it;
        nearest_dist = dist;
      }
    }
    if (nearest_dist < 10.0f) {
      assert(nearest_walker != nullptr);
      mojgame::LOGGER().Info("name: %s, sex: %d, age: %d, height: %d, weight: %d",
                  nearest_walker->property().name(),
                  nearest_walker->property().sex(),
                  nearest_walker->property().age(),
                  nearest_walker->property().height(),
                  nearest_walker->property().weight());
    }
  }
  return 0;
}