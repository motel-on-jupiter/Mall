/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#ifndef CORE_SCENE_CONVENIENCESTORESCENE_H_
#define CORE_SCENE_CONVENIENCESTORESCENE_H_

#include <string>
#include <vector>
#include "core/actor/MallHuman.h"
#include "core/actor/Walker.h"
#include "core/MallGame.h"
#include "core/MallStage.h"

class AutomaticDoor;
class ShopShelf;

class ConvenienceStoreStage : public MallStage {
 public:
  static const size_t kPortalWaypointIdx;
  static const size_t kCashierWaypointIdxTbl[];
  static const size_t kExitWaypointIdx;

  ConvenienceStoreStage();
  virtual ~ConvenienceStoreStage();

  virtual int Initialize(const glm::vec2 &size);
  virtual void Finalize();

  size_t GetCashierNum() const;
  const mojgame::Waypoint &GetPotalWaypoint() const;
  const mojgame::Waypoint *GetCashierWaypoint(size_t idx) const;
  const mojgame::Waypoint &GetExitWaypoint() const;

 private:
  static const glm::vec2 kWaypointPositionTbl[];
};

class ConvenienceStoreAttendant : public MallHuman {
 public:
  explicit ConvenienceStoreAttendant(const glm::vec2 &pos);
  virtual ~ConvenienceStoreAttendant() {}
};

class ConvenienceStoreCustomer : public Walker {
 public:
  static ConvenienceStoreCustomer *Create(ConvenienceStoreStage &stage,
                                          std::vector<ShopShelf *> shelfs,
                                          std::string wanteditem,
                                          unsigned int wantednum);
  virtual ~ConvenienceStoreCustomer() {}

  int Update(float elapsed_time);

 protected:
  ConvenienceStoreCustomer(const mojgame::WaypointGraph &graph, const mojgame::Waypoint &potalpoint,
                           const mojgame::Waypoint &wantedpoint, const mojgame::Waypoint &cashierpoint,
                           const mojgame::Waypoint &exitpoint, std::string wanteditem,
                           unsigned int wantednum);

 private:
  const mojgame::Waypoint &potalpoint_;
  const mojgame::Waypoint &wantedpoint_;
  const mojgame::Waypoint &cashierpoint_;
  const mojgame::Waypoint &exitpoint_;
  std::string wanteditem_;
  unsigned int wantednum_;
};

class ConvenienceStoreScene : public MallBaseGameScene {
 public:
  ConvenienceStoreScene();
  ~ConvenienceStoreScene();

  int Initialize(const glm::vec2 &stage_size);
  void Finalize();
  int Update(float elapsed_time);
  int Draw();
  int OnMouseButtonDown(unsigned char button, const glm::vec2 &cursor_pos);

 private:
  static std::string kShopItemList[];
  struct ShelfInitParam {
    glm::vec2 pos;
    float rot;
    glm::vec2 scale;
    const char *stockitem;
    unsigned int stocknum;
    size_t waypoint;
  };
  static const ShelfInitParam kShelfInitParamTbl[];

  bool initialized_;
  ConvenienceStoreStage stage_;
  AutomaticDoor *autodoor_;
  std::vector<ShopShelf *> shelfs_;
  std::vector<ConvenienceStoreAttendant *> attendants_;
  std::vector<ConvenienceStoreCustomer *> customers_;
};

#endif /* CORE_SCENE_CONVENIENCESTORESCENE_H_ */
