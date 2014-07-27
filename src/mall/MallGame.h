/**
 * Copyright (C) 2014 The Motel On Jupiter
 */

#ifndef MALLGAME_H_
#define MALLGAME_H_

class GLUquadric;
struct MallContext;

class RectangleEntity {
 public:
  RectangleEntity(glm::vec2 pos, glm::vec2 scale);

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

  void Update();
  void SetGoal(GoalNode *goal) { goal_ = goal; }
  bool HasReached() const { return goal_ != nullptr; }

 private:
  GoalNode *goal_;
};

class MallGame {
 public:
  MallGame();
  ~MallGame();

  int Initialize();
  void Finalize();

  void Update(float elapsed_time, glm::vec2 window_size);
  int Draw(glm::vec2 window_size);

 private:
  bool initialized_;
  GoalWalker walker_;
  GoalNode *goal_;
};

#endif /* MALLGAME_H_ */
