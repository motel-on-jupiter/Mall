/**
 * Copyright (C) 2014 The Motel on Jupiter
 */

#ifndef BRIDGESCENE_H_
#define BRIDGESCENE_H_

#include <vector>
#include "mall/actor/Walker.h"
#include "mall/MallGame.h"
#include "mall/MallStage.h"

class BridgeStage : public MallStage {
 public:
  BridgeStage();
  virtual ~BridgeStage();

  virtual int Initialize(const glm::vec2 &size);
  virtual void Finalize();

 private:
  static const glm::vec2 kWaypointPositionTbl[];
};

class BridgeScene : public MallGameSceneInterface {
 public:
  BridgeScene();
  ~BridgeScene();

  int Initialize(const glm::vec2 &stage_size);
  void Finalize();
  void Update(float elapsed_time);
  int Draw(glm::vec2 window_size);
  int OnMouseButtonDown(unsigned char button, int x, int y, glm::vec2 window_size);

 private:
  bool initialized_;
  BridgeStage stage_;
  std::vector<Walker *> walkers_;
};

#endif /* BRIDGESCENE_H_ */
