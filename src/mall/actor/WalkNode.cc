/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "mall/actor/WalkNode.h"

#include <boost/foreach.hpp>

#include "util/logging/Logger.h"

WalkNode::WalkNode(const glm::vec2 &pos) :
  pos_(pos), nextnodes_() {
}

void WalkNode::AddNextNode(WalkNode *node) {
  nextnodes_.push_back(node);
}

WalkNodeGraph::WalkNodeGraph() : nodes_() {
}

WalkNodeGraph::~WalkNodeGraph() {
}

void WalkNodeGraph::AddNode(WalkNode *node) {
  nodes_.push_back(node);
}

void WalkNodeGraph::Clear() {
  BOOST_FOREACH (auto node, nodes_) {
    delete node;
  }
  nodes_.clear();
}


const WalkNode *WalkNodeGraph::CalcNearestNode(const glm::vec2 &pos) const {
  const WalkNode *nearest = nullptr;
  float nearest_len = FLT_MAX;
  BOOST_FOREACH (auto node, nodes_) {
    float len = glm::length(node->pos() - pos);
    if (len < nearest_len) {
      nearest = node;
      nearest_len = len;
    }
  }
  return nearest;
}
