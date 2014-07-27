/**
 * Copyright (C) 2014 The Motel On Jupiter
 */

#ifndef WALKER_H_
#define WALKER_H_

#include "mall/actor/Entity.h"
#include "mall/actor/WalkNode.h"

class GoalWalker : public RectangleEntity {
 public:
  GoalWalker(const glm::vec2 &pos);
  ~GoalWalker();

  void Update();
  void SetGoal(const WalkNode *goal) { goal_ = goal; }
  bool HasReached() const { return goal_ == nullptr; }
#ifdef _DEBUG
  void DebugDraw(const glm::vec2 &window_size);
#endif // _DEBUG

 private:
  const WalkNode *goal_;
};

class NodeWalker : public GoalWalker {
public:
  NodeWalker(const WalkNode &node);
};

#endif /* WALKER_H_ */
