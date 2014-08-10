/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "mall/actor/Walker.h"

#include <GL/glew.h>

#include "util/logging/Logger.h"
#include "util/macro_util.h"
#define GLM_COLOR
#include "util/def/ColorDef.h"

const char *WalkerProperty::kDefaultName = "Smith";

Walker::Walker(const WaypointGraph &graph, const Waypoint &origin, const Waypoint &terminus) :
  RectangleEntity(origin.pos(), 0.0f, glm::vec2(5.0f, 5.0f)),
  navi_(graph), goal_(&origin), reached_(true) {
  navi_.Reroute(origin, terminus);
}

void Walker::Update() {
  if (glm::distance(pos(), goal_->pos()) <= 1.0f) {
    set_pos(goal_->pos());
    reached_ = true;
  }
  if (reached_) {
    const Waypoint *goal = navi_.NextGoal();
    if (goal == nullptr) {
      return;
    }
    reached_ = false;
    goal_ = goal;
  } else {
    set_pos(pos() + glm::normalize(goal_->pos() - pos()));
  }
}

void Walker::Reroute(const Waypoint &terminus) {
  navi_.Reroute(*goal_, terminus);
}

void Walker::Draw() {
  glm::vec3 color;
  if (CheckStatus() == kWalkerRerouting) {
    glColor3fv(glm::value_ptr(kYellowColor));
  } else if (CheckStatus() == kWalkerMoving) {
    glColor3fv(glm::value_ptr(kGreenColor));
  } else {
    glColor3fv(glm::value_ptr(kBlueColor));
  }
  RectangleEntity::Draw();

  if (goal_ != nullptr) {
    glColor3fv(glm::value_ptr(kYellowColor));
    glBegin(GL_LINE_LOOP);
    glVertex2fv(glm::value_ptr(pos()));
    glVertex2fv(glm::value_ptr(goal_->pos()));
    glEnd();
  }
  const Waypoint *terminus = navi_.GetTerminus();
  if (terminus != nullptr) {
    glColor3fv(glm::value_ptr(kRedColor));
    glBegin(GL_LINE_LOOP);
    glVertex2fv(glm::value_ptr(pos()));
    glVertex2fv(glm::value_ptr(terminus->pos()));
    glEnd();
  }
}

Walker::WalkerStatus Walker::CheckStatus() const {
  if (navi_.rerouting()) {
    return kWalkerRerouting;
  }
  if (reached_) {
    return kWalkerStandBy;
  }
  return kWalkerMoving;
}
