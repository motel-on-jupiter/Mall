/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "core/actor/Walker.h"
#include "core/MallTweakerContext.h"
#include "mojgame/catalogue/entity_extention/PlanarEntityRouting.h"
#include "mojgame/includer/gl_include.h"
#include "mojgame/navigation/Waypoint.h"
#include "mojgame/sampler/color_sample.h"

const float Walker::kDefaultMoveSpeed = 5.0f * 1000.0f / 60.0f / 60.0f;
const float Walker::kDefaultTurnSpeed = glm::radians(18000.0f) / 60.0f;

Walker::Walker(float rot, const mojgame::WaypointGraph &graph, const mojgame::Waypoint &origin,
               const mojgame::Waypoint &terminus, float movespeed, float turnspeed) :
  MallHuman(origin.pos(), rot, mojgame::WebColor::kGreen),
  mojgame::PlanarEntityRouting(*this, graph, origin, terminus, movespeed, turnspeed) {
}

int Walker::Update(float elapsed_time) {
  mojgame::PlanarEntityRouting::Update(elapsed_time);
  return 0;
}

void Walker::Draw() {
  if (navi().rerouting()) {
    set_color(mojgame::WebColor::kYellow);
  } else if (HasReached()) {
    set_color(mojgame::WebColor::kNavy);
  } else {
    set_color(mojgame::WebColor::kGreen);
  }
  MallHuman::Draw();

  if (tweaker_ctx.walker_route_visible) {
    if (goal() != nullptr) {
      glColor3ubv(mojgame::WebColor::kYellow);
      glBegin(GL_LINE_LOOP);
      glVertex2fv(glm::value_ptr(pos()));
      glVertex2fv(glm::value_ptr(goal()->pos()));
      glEnd();
    }
    const mojgame::Waypoint *terminus = navi().GetTerminus();
    if (terminus != nullptr) {
      glColor3ubv(mojgame::WebColor::kRed);
      glBegin(GL_LINE_LOOP);
      glVertex2fv(glm::value_ptr(pos()));
      glVertex2fv(glm::value_ptr(terminus->pos()));
      glEnd();
    }
  }
}
