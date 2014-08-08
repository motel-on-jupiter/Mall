/**
 * Copyright (C) 2014 The Motel On Jupiter
 */

#ifndef BRIDGETRAFFICCASE_H_
#define BRIDGETRAFFICCASE_H_

#include "mall/MallGame.h"
#include "mall/MallStage.h"

class BridgeStage : public MallStage {
 public:
  BridgeStage();
  virtual ~BridgeStage();

  virtual int Initialize(const glm::vec2 &window_size);
  virtual void Finalize();

 private:
  static const glm::vec2 kWaypointPositionTbl[];
};

class BridgeTrafficCase : public MallGameCaseInterface {
 public:
  BridgeTrafficCase();
  ~BridgeTrafficCase();

  int Initialize(const glm::vec2 &window_size);
  void Finalize();
  void Update(float elapsed_time);
  int Draw(glm::vec2 window_size);
  int OnMouseButtonDown(unsigned char button, int x, int y, glm::vec2 window_size);

 private:
  bool initialized_;
  BridgeStage stage_;
};

#endif /* BRIDGETRAFFICCASE_H_ */
