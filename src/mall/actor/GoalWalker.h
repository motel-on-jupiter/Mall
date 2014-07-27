/**
 * Copyright (C) 2014 The Motel On Jupiter
 */

#ifndef GALLWALKER_H_
#define GALLWALKER_H_

class RectangleEntity {
 public:
  RectangleEntity(glm::vec2 pos, glm::vec2 scale);
  virtual ~RectangleEntity() {}

  void Draw(glm::vec2 window_size);

  glm::vec2 pos() const { return pos_; }
  void set_pos(const glm::vec2 &pos) { pos_ = pos; }

 private:
  glm::vec2 pos_;
  glm::vec2 scale_;
};

class GoalNode : public RectangleEntity {
public:
  GoalNode(glm::vec2 pos);
};

class GoalWalker : public RectangleEntity {
 public:
  GoalWalker(glm::vec2 pos);
  ~GoalWalker();

  void Update();
  void SetGoal(GoalNode *goal) { free(goal_); goal_ = goal; }
  bool HasReached() const { return goal_ == nullptr; }

 private:
  GoalNode *goal_;
};

#endif /* GALLWALKER_H_ */
