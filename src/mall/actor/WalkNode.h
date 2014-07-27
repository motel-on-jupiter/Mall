/**
 * Copyright (C) 2014 The Motel On Jupiter
 */

#ifndef WALKNODE_H_
#define WALKNODE_H_

#include <vector>
#include "mall/actor/Entity.h"

class WalkNode : public PointEntity {
public:
  WalkNode(const glm::vec2 &pos);
  virtual ~WalkNode() {}

  void addNextNode(WalkNode *node);

  const std::vector<WalkNode*>& nextnodes() const { return nextnodes_; }

private:
  std::vector<WalkNode *> nextnodes_;
};

class WalkNodeMap {
 public:
  static const float kMapNodeInterval;

  WalkNodeMap();
  ~WalkNodeMap();

  int Initialize(const glm::vec2 &window_size);
  void Finalize();

  void Draw(const glm::vec2 &window_size);

  const std::vector<WalkNode*>& nodes() const { return nodes_; }

 private:
  std::vector<WalkNode *> nodes_;
};

#endif /* WALKNODE_H_ */
