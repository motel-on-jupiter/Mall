/**
 * Copyright (C) 2014 The Motel On Jupiter
 */

#ifndef MALLGAME_H_
#define MALLGAME_H_

#include "mall/actor/GoalWalker.h"

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
