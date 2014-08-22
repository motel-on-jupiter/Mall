/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#ifndef CONVENIENCESTORESCENE_H_
#define CONVENIENCESTORESCENE_H_

#include <vector>
#include "mall/actor/MallHuman.h"
#include "mall/MallGame.h"
#include "mall/MallStage.h"

class AutomaticDoor;
class ShopShelf;
class Walker;

class ConvenienceStoreAttendant : public MallHuman {
 public:
  explicit ConvenienceStoreAttendant(const glm::vec2 &pos);
  virtual ~ConvenienceStoreAttendant() {}

  virtual void Draw();
};

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
  static const glm::vec2 kShelfPositionTbl[];
  static const float kShelfRotationTbl[];
  static const glm::vec2 kShelfScaleTbl[];

  bool initialized_;
  ConvenienceStoreStage stage_;
  AutomaticDoor *autodoor_;
  std::vector<ShopShelf *> shelfs_;
  std::vector<ConvenienceStoreAttendant *> attendants_;
  std::vector<Walker *> walkers_;
};

#endif /* CONVENIENCESTORESCENE_H_ */
