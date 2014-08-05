/**
 * Copyright (C) 2014 The Motel On Jupiter
 */

#ifndef WALKER_H_
#define WALKER_H_

#include "mall/actor/Entity.h"
#include "navigation/Navigator.h"

class Walker : public RectangleEntity {
public:
  enum WalkerStatus {
    kWalkerStandBy,
    kWalkerMoving,
    kWalkerRerouting,
  };

  Walker(const WaypointGraph &graph, const Waypoint &origin, const Waypoint &terminus);
  virtual ~Walker() {}

  void Update();
  void Reroute(const Waypoint &terminus);
  void Draw(const glm::vec2 &window_size);
  WalkerStatus CheckStatus() const;

private:
  Navigator navi_;
  const Waypoint *goal_;
  bool reached_;
};

#endif /* WALKER_H_ */
