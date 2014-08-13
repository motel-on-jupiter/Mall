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
  static const float Automobile::kDefaultSpeed;

  Automobile(const WaypointGraph &graph, const Waypoint &origin,
             const Waypoint &terminus, float speed = kDefaultSpeed);
  virtual ~Automobile() {}

  virtual void Update(float elapsed_time);
};

#endif /* AUTOMOBILE_H_ */
