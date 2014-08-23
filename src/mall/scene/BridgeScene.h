/**
 * Copyright (C) 2014 The Motel on Jupiter
 */

#ifndef BRIDGESCENE_H_
#define BRIDGESCENE_H_

#include <vector>
#include "mall/MallGame.h"
#include "mall/MallStage.h"

class Automobile;
class Walker;

class BridgeStage : public MallStage {
 public:
  BridgeStage();
  virtual ~BridgeStage();

  virtual int Initialize(const glm::vec2 &size);
  virtual void Finalize();

 private:
  static const glm::vec2 kSidewalkWaypointPosTbl[];
  static const glm::vec2 kRoadwayWaypointPosTbl[];
};

class BridgeScene : public MallGameSceneInterface {
 public:
  BridgeScene();
  ~BridgeScene();

  int Initialize(const glm::vec2 &stage_size);
  void Finalize();
  int Update(float elapsed_time);
  int Draw();
  int OnMouseButtonDown(unsigned char button, const glm::vec2 &cursor_pos);

 private:
  bool initialized_;
  BridgeStage stage_;
  std::vector<Walker *> walkers_;
  std::vector<Automobile *> automobiles_;
  Walker *lastgenwalkers_[4];
  Automobile *lastgenautomobiles_[2];
};

#endif /* BRIDGESCENE_H_ */
