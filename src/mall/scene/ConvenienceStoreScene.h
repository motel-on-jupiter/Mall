/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#ifndef CONVENIENCESTORESCENE_H_
#define CONVENIENCESTORESCENE_H_

#include <string>
#include <vector>
#include "mall/actor/MallHuman.h"
#include "mall/actor/Walker.h"
#include "mall/MallGame.h"
#include "mall/MallStage.h"

class AutomaticDoor;
class ShopShelf;

class ConvenienceStoreAttendant : public MallHuman {
 public:
  explicit ConvenienceStoreAttendant(const glm::vec2 &pos);
  virtual ~ConvenienceStoreAttendant() {}
};

class ConvenienceStoreCustomer : public Walker {
 public:
  ConvenienceStoreCustomer(const WaypointGraph &graph, const Waypoint &potalpoint,
                           const Waypoint &wantedpoint, const Waypoint &cashierpoint,
                           const Waypoint &exitpoint, std::string wanteditem,
                           unsigned int wantednum);
  virtual ~ConvenienceStoreCustomer() {}

  int Update(float elapsed_time);

 private:
  const Waypoint &potalpoint_;
  const Waypoint &wantedpoint_;
  const Waypoint &cashierpoint_;
  const Waypoint &exitpoint_;
  std::string wanteditem_;
  unsigned int wantednum_;
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
  struct ShelfInitParam {
    glm::vec2 pos;
    float rot;
    glm::vec2 scale;
    const char *stockitem;
    unsigned int stocknum;
    size_t waypoint;
  };
  static const ShelfInitParam kShelfInitParamTbl[];
  static const size_t kPortalWaypointIdx;
  static const size_t kCashierWaypointIdxTbl[];
  static const size_t kExitWaypointIdx;

  bool initialized_;
  ConvenienceStoreStage stage_;
  AutomaticDoor *autodoor_;
  std::vector<ShopShelf *> shelfs_;
  std::vector<ConvenienceStoreAttendant *> attendants_;
  std::vector<ConvenienceStoreCustomer *> customers_;
};

#endif /* CONVENIENCESTORESCENE_H_ */
