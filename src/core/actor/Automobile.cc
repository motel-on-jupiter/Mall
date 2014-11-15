/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "core/actor/Automobile.h"
#include "mojgame/entity/PlanarEntity.h"
#include "mojgame/catalogue/entity_extention/PlanarEntityDraw.h"
#include "mojgame/catalogue/entity_extention/PlanarEntityRouting.h"
#include "mojgame/sampler/color_sample.h"

const float Automobile::kDefaultMoveSpeed = 20.0f * 1000.0f / 60.0f / 60.0f;
const float Automobile::kDefaultTurnSpeed = glm::radians(360.0f);
const glm::vec2 Automobile::kScale = glm::vec2(1.71f, 4.83f);

Automobile::Automobile(float rot, const mojgame::WaypointGraph &graph,
                       const mojgame::Waypoint &origin,
                       const mojgame::Waypoint &terminus, float movespeed,
                       float turnspeed)
    : mojgame::PlanarEntity(origin.pos(), rot, kScale),
      mojgame::EntityRectangleDraw(*this, true, mojgame::WebColor::kGreen),
      mojgame::PlanarEntityRouting(*this, graph, origin, terminus, movespeed,
                                   turnspeed) {
}

void Automobile::Update(float elapsed_time) {
  mojgame::PlanarEntityRouting::Update(elapsed_time);
}
