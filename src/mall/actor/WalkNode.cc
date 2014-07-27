/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "mall/actor/WalkNode.h"

#include <boost/foreach.hpp>

#include "util/logging/Logger.h"

WalkNode::WalkNode(const glm::vec2 &pos) :
  PointEntity(pos), nextnodes_() {
}

void WalkNode::addNextNode(WalkNode *node) {
  nextnodes_.push_back(node);
}

const float WalkNodeMap::kMapNodeInterval = 40.0f;

WalkNodeMap::WalkNodeMap() : nodes_() {
}

WalkNodeMap::~WalkNodeMap() {
}

int WalkNodeMap::Initialize(const glm::vec2 &window_size) {
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
        node->addNextNode(nodes_[(raw - 1) * max_column + column]);
        nodes_[(raw - 1) * max_column + column]->addNextNode(node);
      }
      if (column != 0) {
        node->addNextNode(nodes_[raw * max_column + (column - 1)]);
        nodes_[raw * max_column + (column - 1)]->addNextNode(node);
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
