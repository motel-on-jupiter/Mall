/**
 * Copyright (C) 2014 The Motel On Jupiter
 */

#include "mall/stage/Stage.h"
#include <boost/foreach.hpp>
#define GLM_COLOR
#include "util/def/ColorDef.h"
#include "util/logging/Logger.h"

Stage::Stage() : nodemap_() {
}

Stage::~Stage() {
}

void Stage::Draw(const glm::vec2 &window_size) {
  glColor3fv(glm::value_ptr(kWhiteColor));
  glPointSize(0.1f);
  glBegin(GL_POINTS);
  BOOST_FOREACH (auto node, nodemap_.nodes()) {
    glVertex2f(node->pos().x / window_size.x * 2.0f - 1.0f,
               node->pos().y / window_size.y * 2.0f - 1.0f);
  }
  glEnd();
}

const float GridStage::kMapNodeInterval = 70.0f;

GridStage::GridStage() : Stage() {
}

GridStage::~GridStage() {
}

int GridStage::Initialize(const glm::vec2 &window_size) {
  int max_raw = static_cast<int>(window_size.x / kMapNodeInterval);
  int max_column = static_cast<int>(window_size.y / kMapNodeInterval);
  for (int raw = 0; raw < max_raw; ++raw) {
    for (int column = 0; column < max_column; ++column) {
      WalkNode *node = new WalkNode(glm::vec2(kMapNodeInterval * static_cast<float>(raw),
                                              kMapNodeInterval * static_cast<float>(column)));
      if (node == nullptr) {
        LOGGER.Error("Failed to allocate the walk node object");
        return -1;
      }

      if (raw != 0) {
        node->AddNextNode(const_graph().nodes()[(raw - 1) * max_column + column]);
        nodemap().nodes()[(raw - 1) * max_column + column]->AddNextNode(node);
      }
      if (column != 0) {
        node->AddNextNode(const_graph().nodes()[raw * max_column + (column - 1)]);
        nodemap().nodes()[raw * max_column + (column - 1)]->AddNextNode(node);
      }

      nodemap().AddNode(node);
    }
  }
  return 0;
}

void GridStage::Finalize() {
  nodemap().Clear();
}

