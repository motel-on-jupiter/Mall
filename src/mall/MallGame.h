/**
 * Copyright (C) 2014 The Motel On Jupiter
 */

#ifndef MALLGAME_H_
#define MALLGAME_H_

#include "mall/actor/NodeWalker.h"
#include "mall/actor/WalkNode.h"

class MallGame {
 public:
  MallGame();
  ~MallGame();

  int Initialize(const glm::vec2 &window_size);
  void Finalize();

  void Update(float elapsed_time);
  int Draw(glm::vec2 window_size);

 private:
  static const int MallGame::kNumWalkWalkers;

  bool initialized_;
  WalkNodeMap nodemap_;
  std::vector<NodeMapWalker *> walkers_;
};

#endif /* MALLGAME_H_ */
