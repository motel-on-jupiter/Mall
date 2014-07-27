/**
 * Copyright (C) 2014 The Motel On Jupiter
 */

#ifndef MALLGAME_H_
#define MALLGAME_H_

#include "mall/actor/GoalWalker.h"

class MallGame {
 public:
  MallGame(const glm::vec2 &window_size);
  ~MallGame();

  int Initialize();
  void Finalize();

  void Update(float elapsed_time, glm::vec2 window_size);
  int Draw(glm::vec2 window_size);

 private:
  static const int MallGame::kNumWalkWalkers;

  bool initialized_;
  std::vector<GoalWalker *> walkers_;
};

#endif /* MALLGAME_H_ */
