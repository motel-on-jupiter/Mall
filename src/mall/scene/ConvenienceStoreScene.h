/**
 * Copyright (C) 2014 The Motel on Jupiter
 */

#ifndef CONVENIENCESTORESCENE_H_
#define CONVENIENCESTORESCENE_H_

#include <vector>
#include "mall/actor/Walker.h"
#include "mall/MallGame.h"
#include "mall/MallStage.h"

class ConvenienceStoreStage : public MallStage {
 public:
  ConvenienceStoreStage();
  virtual ~ConvenienceStoreStage();

  virtual int Initialize(const glm::vec2 &size);
  virtual void Finalize();

 private:
  static const glm::vec2 kWaypointPositionTbl[];
};

class ConvenienceStoreScene : public MallGameSceneInterface {
 public:
  ConvenienceStoreScene();
  ~ConvenienceStoreScene();

  int Initialize(const glm::vec2 &stage_size);
  void Finalize();
  int Update(float elapsed_time);
  int Draw();
  int OnMouseButtonDown(unsigned char button, const glm::vec2 &cursor_pos);

 private:
  bool initialized_;
  ConvenienceStoreStage stage_;
  Walker *walker_;
};

#endif /* CONVENIENCESTORESCENE_H_ */