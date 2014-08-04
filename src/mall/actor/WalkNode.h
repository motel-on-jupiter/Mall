/**
 * Copyright (C) 2014 The Motel On Jupiter
 */

#ifndef WALKNODE_H_
#define WALKNODE_H_

#include <vector>

class WalkNode {
public:
  WalkNode(const glm::vec2 &pos);
  virtual ~WalkNode() {}

  void AddNextNode(WalkNode *node);

  const glm::vec2& pos() const { return pos_; }
  const std::vector<WalkNode*>& nextnodes() const { return nextnodes_; }

private:
  glm::vec2 pos_;
  std::vector<WalkNode *> nextnodes_;
};

class WalkNodeGraph {
 public:
  WalkNodeGraph();
  ~WalkNodeGraph();

  int Initialize(const glm::vec2 &window_size);
  void Finalize();

  void AddNode(WalkNode *node);
  void Clear();

  const WalkNode *CalcNearestNode (const glm::vec2 &pos) const ;

  const std::vector<WalkNode*>& nodes() const { return nodes_; }

 private:
  std::vector<WalkNode *> nodes_;
};

#endif /* WALKNODE_H_ */
