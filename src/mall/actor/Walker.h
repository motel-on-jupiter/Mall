/**
 * Copyright (C) 2014 The Motel On Jupiter
 */

#ifndef GALLWALKER_H_
#define GALLWALKER_H_

class RectangleEntity {
 public:
  RectangleEntity(const glm::vec2 &pos, const glm::vec2 &scale);
  virtual ~RectangleEntity() {}

  void Draw(const glm::vec2 &window_size);

  glm::vec2 pos() const { return pos_; }
  void set_pos(const glm::vec2 &pos) { pos_ = pos; }

 private:
  glm::vec2 pos_;
  glm::vec2 scale_;
};

class WalkNode : public RectangleEntity {
public:
  WalkNode(const glm::vec2 &pos);
};

class GoalWalker : public RectangleEntity {
 public:
  GoalWalker(const glm::vec2 &pos);
  ~GoalWalker();

  void Update();
  void SetGoal(WalkNode *goal) { free(goal_); goal_ = goal; }
  bool HasReached() const { return goal_ == nullptr; }
#ifdef _DEBUG
  void DebugDraw(const glm::vec2 &window_size);
#endif // _DEBUG

 private:
  WalkNode *goal_;
};

class NodeWalker : public GoalWalker {
public:
  NodeWalker(const WalkNode &node);
};

#endif /* GALLWALKER_H_ */
