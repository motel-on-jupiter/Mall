/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "mall/actor/WalkNode.h"

#include <boost/foreach.hpp>

#include "util/logging/Logger.h"

WalkNode::WalkNode(const glm::vec2 &pos) : PointEntity(pos) {
}

const float WalkNodeMap::kMapNodeInterval = 10.0f;

WalkNodeMap::WalkNodeMap() : nodes_() {
}

WalkNodeMap::~WalkNodeMap() {
}

int WalkNodeMap::Initialize(const glm::vec2 &window_size) {
  for (int raw = 0; ; ++raw) {
    float node_pos_x = kMapNodeInterval * static_cast<float>(raw);
    if (node_pos_x > window_size.x) {
      break;
    }
    for (int column = 0; ; ++column) {
      float node_pos_y = kMapNodeInterval * static_cast<float>(column);
      if (node_pos_y > window_size.y) {
        break;
      }
      WalkNode *node = new WalkNode(glm::vec2(node_pos_x, node_pos_y));
      if (node == nullptr) {
        LOGGER.Error("Failed to allocate the walk node object");
        return -1;
      }
      nodes_.push_back(node);
    }
  }
  return 0;
}

void WalkNodeMap::Finalize() {
  BOOST_FOREACH (auto node, nodes_) {
    delete(node);
  }
}

void WalkNodeMap::Draw(const glm::vec2 &window_size) {
  BOOST_FOREACH (auto node, nodes_) {
    node->Draw(window_size);
  }
}
