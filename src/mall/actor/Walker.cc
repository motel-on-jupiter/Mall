/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "mall/actor/Walker.h"
#include <GL/glew.h>
#include "entity/EntityRouting.h"
#include "util/def/ColorDef.h"

const float Walker::kDefaultWalkSpeed = 5.0f * 1000.0f / 60.0f / 60.0f;

Walker::Walker(const WaypointGraph &graph, const Waypoint &origin,
               const Waypoint &terminus, float speed) :
  MallHuman(origin.pos(), 0.0f),
  EntityRouting(*this, graph, origin, terminus, speed) {
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
