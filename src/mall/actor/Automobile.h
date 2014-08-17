/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#ifndef AUTOMOBILE_H_
#define AUTOMOBILE_H_

#include "entity/BaseEntity.h"
#include "entity/EntityDraw.h"
#include "entity/EntityRouting.h"

class Automobile :
    public BaseEntity, public EntityRectangleDraw, public EntityRouting {
public:
  static const float Automobile::kDefaultMoveSpeed;
  static const float Automobile::kDefaultTurnSpeed;

  Automobile(float rot, const WaypointGraph &graph, const Waypoint &origin,
             const Waypoint &terminus, float movespeed = kDefaultMoveSpeed,
             float turnspeed = kDefaultTurnSpeed);
  virtual ~Automobile() {}

  virtual void Update(float elapsed_time);
};

#endif /* AUTOMOBILE_H_ */
