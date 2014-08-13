/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "mall/actor/Automobile.h"
#include "entity/BaseEntity.h"
#include "entity/EntityDraw.h"
#include "entity/EntityRouting.h"

const float Automobile::kDefaultSpeed = 30.0f * 1000.0f / 60.0f / 60.0f;

Automobile::Automobile(const WaypointGraph &graph, const Waypoint &origin,
                       const Waypoint &terminus, float speed) :
  BaseEntity(origin.pos(), 0.0f, glm::vec2(1.71f, 4.83f)),
  EntityRectangleDraw(*this, true),
  EntityRouting(*this, graph, origin, terminus, speed) {
}

void Automobile::Update(float elapsed_time) {
  EntityRouting::Update(elapsed_time);
}
