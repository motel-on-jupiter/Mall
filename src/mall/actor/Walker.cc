/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "mall/actor/Walker.h"
#include <GL/glew.h>
#include "entity/EntityRouting.h"
#include "mall/MallTweakerContext.h"
#include "util/def/ColorDef.h"

const float Walker::kDefaultMoveSpeed = 5.0f * 1000.0f / 60.0f / 60.0f;
const float Walker::kDefaultTurnSpeed = glm::radians(5.0f);

Walker::Walker(const WaypointGraph &graph, const Waypoint &origin,
               const Waypoint &terminus, float movespeed, float turnspeed) :
  MallHuman(origin.pos(), 0.0f),
  EntityRouting(*this, graph, origin, terminus, movespeed, turnspeed) {
}

void Walker::Update(float elapsed_time) {
  EntityRouting::Update(elapsed_time);
}

void Walker::Draw() {
  glm::vec3 color;
  if (navi().rerouting()) {
    glColor3ubv(WebColor::kYellow);
  } else if (reached()) {
    glColor3ubv(WebColor::kNavy);
  } else {
    glColor3ubv(WebColor::kGreen);
  }
  MallHuman::Draw();

  if (tweaker_ctx.walker_route_visible) {
    if (goal() != nullptr) {
      glColor3ubv(WebColor::kYellow);
      glBegin(GL_LINE_LOOP);
      glVertex2fv(glm::value_ptr(pos()));
      glVertex2fv(glm::value_ptr(goal()->pos()));
      glEnd();
    }
    const Waypoint *terminus = navi().GetTerminus();
    if (terminus != nullptr) {
      glColor3ubv(WebColor::kRed);
      glBegin(GL_LINE_LOOP);
      glVertex2fv(glm::value_ptr(pos()));
      glVertex2fv(glm::value_ptr(terminus->pos()));
      glEnd();
    }
  }
}
