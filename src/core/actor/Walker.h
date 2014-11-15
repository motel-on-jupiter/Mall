/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#ifndef CORE_ACTOR_WALKER_H_
#define CORE_ACTOR_WALKER_H_

#include "core/actor/MallHuman.h"
#include "mojgame/catalogue/entity_extention/PlanarEntityRouting.h"
#include "mojgame/navigation/Waypoint.h"

class Walker : public MallHuman, public mojgame::PlanarEntityRouting {
public:
  static const float kDefaultMoveSpeed;
  static const float kDefaultTurnSpeed;

  Walker(float rot, const mojgame::WaypointGraph &graph, const mojgame::Waypoint &origin,
         const mojgame::Waypoint &terminus, float movespeed = kDefaultMoveSpeed,
         float turnspeed = kDefaultTurnSpeed);
  virtual ~Walker() {}

  virtual int Update(float elapsed_time);
  virtual void Draw();
};

#endif /* CORE_ACTOR_WALKER_H_ */
