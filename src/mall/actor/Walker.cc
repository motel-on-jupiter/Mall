/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "mall/actor/Walker.h"

#include <GL/glew.h>

#include "util/logging/Logger.h"
#include "util/macro_util.h"
#define GLM_COLOR
#include "util/def/ColorDef.h"

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

void Walker::Draw(const glm::vec2 &window_size) {
  glm::vec3 color;
  if (CheckStatus() == kWalkerRerouting) {
    color = kYellowColor;
  } else if (CheckStatus() == kWalkerMoving) {
    color = kGreenColor;
  } else {
    color = kBlueColor;
  }
  RectangleEntity::Draw(window_size, color);

  if (goal_ != nullptr) {
    glColor3fv(glm::value_ptr(kYellowColor));
    glBegin(GL_LINE_LOOP);
    glVertex2f(pos().x / window_size.x * 2.0f - 1.0f, pos().y / window_size.y * 2.0f - 1.0f);
    glVertex2f(goal_->pos().x / window_size.x * 2.0f - 1.0f, goal_->pos().y / window_size.y * 2.0f - 1.0f);
    glEnd();
  }
  const Waypoint *terminus = navi_.GetTerminus();
  if (terminus != nullptr) {
    glColor3fv(glm::value_ptr(kRedColor));
    glBegin(GL_LINE_LOOP);
    glVertex2f(pos().x / window_size.x * 2.0f - 1.0f, pos().y / window_size.y * 2.0f - 1.0f);
    glVertex2f(terminus->pos().x / window_size.x * 2.0f - 1.0f, terminus->pos().y / window_size.y * 2.0f - 1.0f);
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
