/**
 * Copyright (C) 2014 The Motel on Jupiter
 */

#ifndef GRIDSCENE_H_
#define GRIDSCENE_H_

#include "mall/MallGame.h"
#include "mall/MallStage.h"

class Walker;

class GridStage : public MallStage {
 public:
  static const float kGridInterval;

  GridStage();
  virtual ~GridStage();

  virtual int Initialize(const glm::vec2 &size);
  virtual void Finalize();
};

class RoughGridStage : public GridStage {
 public:
  RoughGridStage();
  virtual ~RoughGridStage();

  virtual int Initialize(const glm::vec2 &size);
};

class GridScene : public MallBaseGameScene {
 public:
  GridScene();
  ~GridScene();

  int Initialize(const glm::vec2 &stage_size);
  void Finalize();
  int Update(float elapsed_time);
  int Draw();
  int OnMouseButtonDown(unsigned char button, const glm::vec2 &cursor_pos);

 private:
  static const int kNumWalkWalkers;

  bool initialized_;
  RoughGridStage stage_;
  std::vector<Walker *> walkers_;
};

#endif /* GRIDSCENE_H_ */
