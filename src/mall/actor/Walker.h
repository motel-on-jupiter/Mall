/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#ifndef WALKER_H_
#define WALKER_H_

#include "entity/EntityRouting.h"
#include "mall/actor/MallHuman.h"

class Walker : public MallHuman, public EntityRouting {
public:
  static const float kDefaultWalkSpeed;

  Walker(const WaypointGraph &graph, const Waypoint &origin,
         const Waypoint &terminus, float speed = kDefaultWalkSpeed);
  virtual ~Walker() {}

  virtual void Update(float elapsed_time);
  virtual void Draw();
};

#endif /* WALKER_H_ */
