/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#ifndef AUTOMOBILE_H_
#define AUTOMOBILE_H_

#include "mojgame/entity/PlanarEntity.h"
#include "mojgame/catalogue/entity_extention/PlanarEntityDraw.h"
#include "mojgame/catalogue/entity_extention/PlanarEntityRouting.h"

class Automobile : public mojgame::PlanarEntity,
    public mojgame::EntityRectangleDraw, public mojgame::PlanarEntityRouting {
 public:
  static const float kDefaultMoveSpeed;
  static const float kDefaultTurnSpeed;
  static const glm::vec2 kScale;

  Automobile(float rot, const mojgame::WaypointGraph &graph,
             const mojgame::Waypoint &origin, const mojgame::Waypoint &terminus,
             float movespeed = kDefaultMoveSpeed, float turnspeed =
                 kDefaultTurnSpeed);
  virtual ~Automobile() {
  }

  virtual void Update(float elapsed_time);
};

#endif /* AUTOMOBILE_H_ */
