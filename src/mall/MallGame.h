/**
 * Copyright (C) 2014 The Motel On Jupiter
 */

#ifndef MALLGAME_H_
#define MALLGAME_H_

#include "mall/actor/Walker.h"
#include "mall/stage/Stage.h"

class MallGame {
 public:
  MallGame();
  ~MallGame();

  int Initialize(const glm::vec2 &window_size);
  void Finalize();
  void Update(float elapsed_time);
  int Draw(glm::vec2 window_size);
  int OnMouseButtonDown(Uint8 button, Sint32 x, Sint32 y, glm::vec2 window_size);

 private:
  static const int MallGame::kNumWalkWalkers;

  bool initialized_;
  GridStage stage_;
  std::vector<Walker *> walkers_;
};

#endif /* MALLGAME_H_ */
