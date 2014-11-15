/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "core/actor/Automobile.h"
#include "entity/BaseEntity.h"
#include "entity/EntityDraw.h"
#include "entity/EntityRouting.h"
#include "util/color_sample.h"

const float Automobile::kDefaultMoveSpeed = 20.0f * 1000.0f / 60.0f / 60.0f;
const float Automobile::kDefaultTurnSpeed = glm::radians(360.0f);
const glm::vec2 Automobile::kScale = glm::vec2(1.71f, 4.83f);

Automobile::Automobile(float rot, const WaypointGraph &graph, const Waypoint &origin,
                       const Waypoint &terminus, float movespeed, float turnspeed) :
  BaseEntity(origin.pos(), rot, kScale),
  EntityRectangleDraw(*this, true, WebColor::kGreen),
  EntityRouting(*this, graph, origin, terminus, movespeed, turnspeed) {
}

void Automobile::Update(float elapsed_time) {
  EntityRouting::Update(elapsed_time);
}
