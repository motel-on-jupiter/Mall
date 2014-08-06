/**
 * Copyright (C) 2014 The Motel On Jupiter
 */

#include "mall/stage/Stage.h"
#include <boost/foreach.hpp>
#define GLM_COLOR
#include "util/def/ColorDef.h"
#include "util/logging/Logger.h"

Stage::Stage() : graph_() {
}

Stage::~Stage() {
}

void Stage::Draw(const glm::vec2 &window_size) {
  glColor3fv(glm::value_ptr(kWhiteColor));
  glPointSize(0.1f);
  glBegin(GL_POINTS);
  BOOST_FOREACH(auto point, graph_.points()) {
    glVertex2f(point->pos().x / window_size.x * 2.0f - 1.0f,
               point->pos().y / window_size.y * 2.0f - 1.0f);
  }
  glEnd();
}

const float GridStage::kGridInterval = 70.0f;

GridStage::GridStage() : Stage() {
}

GridStage::~GridStage() {
}

int GridStage::Initialize(const glm::vec2 &window_size) {
  int max_raw = static_cast<int>(window_size.x / kGridInterval);
  int max_column = static_cast<int>(window_size.y / kGridInterval);
  for (int raw = 0; raw < max_raw; ++raw) {
    for (int column = 0; column < max_column; ++column) {
      Waypoint *point = new Waypoint(glm::vec2(kGridInterval * (static_cast<float>(raw) + 0.5f),
                                               kGridInterval * (static_cast<float>(column) + 0.5f)));
      if (point == nullptr) {
        LOGGER.Error("Failed to allocate the waypoint object");
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

int RoughGridStage::Initialize(const glm::vec2 &window_size) {
  int ret = GridStage::Initialize(window_size);
  if (ret < 0) {
    return ret;
  }
  for (auto it = graph().points().begin();
       it != graph().points().end();
       ++it) {
    (*it)->RemoveNextPoint((*it)->nextpoints()[rand() % (*it)->nextpoints().size()]);
  }
  return 0;
}
