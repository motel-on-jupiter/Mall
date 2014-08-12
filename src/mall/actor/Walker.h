/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#ifndef WALKER_H_
#define WALKER_H_

#include "mall/actor/MallHuman.h"
#include "navigation/Navigator.h"

class Walker : public MallHuman {
public:
  enum WalkerStatus {
    kWalkerStandBy,
    kWalkerMoving,
    kWalkerRerouting,
  };
  static const float kDefaultWalkSpeed;

  Walker(const WaypointGraph &graph, const Waypoint &origin,
         const Waypoint &terminus, float speed = kDefaultWalkSpeed);
  virtual ~Walker() {}

  virtual void Update(float elapsed_time);
  void Reroute(const Waypoint &terminus);
  virtual void Draw();
  WalkerStatus CheckStatus() const;

  Navigator &navi() { return navi_; }

private:
  Navigator navi_;
  const Waypoint *goal_;
  bool reached_;
  float speed_;
};

#endif /* WALKER_H_ */
