/**
 * Copyright (C) 2014 The Motel On Jupiter
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

  virtual int Initialize(const glm::vec2 &window_size);
  virtual void Finalize();
};

class RoughGridStage : public GridStage {
 public:
  RoughGridStage();
  virtual ~RoughGridStage();

  virtual int Initialize(const glm::vec2 &window_size);
};

class GridScene : public MallGameSceneInterface {
 public:
  GridScene();
  ~GridScene();

  int Initialize(const glm::vec2 &window_size);
  void Finalize();
  void Update(float elapsed_time);
  int Draw(glm::vec2 window_size);
  int OnMouseButtonDown(unsigned char button, int x, int y, glm::vec2 window_size);

 private:
  static const int kNumWalkWalkers;

  bool initialized_;
  RoughGridStage stage_;
  std::vector<Walker *> walkers_;
};

#endif /* GRIDSCENE_H_ */
