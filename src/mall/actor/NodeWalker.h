/**
 * Copyright (C) 2014 The Motel On Jupiter
 */

#ifndef NODEWALKER_H_
#define NODEWALKER_H_

#include <boost/noncopyable.hpp>

#include "mall/actor/Entity.h"
#include "mall/actor/WalkNode.h"

class NodeWalker : public RectangleEntity {
 public:
  NodeWalker(const WalkNode &start);
  virtual ~NodeWalker() {}

  virtual void Update();
  void SetGoal(const WalkNode *goal) { goal_ = goal; arrived_ = false; }
  virtual void DrawApproach(const glm::vec2 &window_size);

  virtual bool arrived() const { return arrived_; }

  const WalkNode* goal() const { return goal_; }

 protected:
  virtual void SelectNextGoal(const WalkNode *current_goal);

 private:
  const WalkNode *goal_;
  bool arrived_;
};

class NodeGraphWalker : public NodeWalker, private boost::noncopyable {
public:
  NodeGraphWalker(const WalkNode &start, const WalkNodeGraph &graph);
  virtual ~NodeGraphWalker();

  int UpdateFinalGoal(const WalkNode *finalgoal);
  virtual void DrawApproach(const glm::vec2 &window_size);

protected:
  virtual void SelectNextGoal(const WalkNode *current_goal);

private:
  int BuildTravelNodeListImpl(const WalkNode *node, const WalkNode *finalgoal, std::vector<const WalkNode *> &breadcrumbs, std::vector<const WalkNode *> **minlist);
  int BuildTravelNodeList(const WalkNode *finalgoal);

  const WalkNodeGraph &graph_;
  std::vector<const WalkNode *> *travelnodelist_;
  const WalkNode *finalgoal_;
};

class RandomNodeGraphWalker : public NodeWalker, private boost::noncopyable {
public:
  RandomNodeGraphWalker(const WalkNode &start, const WalkNodeGraph &graph);

  virtual void SelectNextGoal(const WalkNode *current_goal);

protected:
  virtual bool arrived() const { return NodeWalker::arrived(); }

private:
  const WalkNodeGraph &graph_;
};

#include "mall/actor/NodeWalker.inl"

#endif /* NODEWALKER_H_ */
