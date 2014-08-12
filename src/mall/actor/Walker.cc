/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "mall/actor/Walker.h"
#include <GL/glew.h>
#include "util/def/ColorDef.h"

const float Walker::kDefaultWalkSpeed = 5.0f * 1000.0f / 60.0f / 60.0f;

Walker::Walker(const WaypointGraph &graph, const Waypoint &origin,
               const Waypoint &terminus, float speed) :
  MallHuman(origin.pos(), 0.0f),
  navi_(graph),
  goal_(&origin),
  reached_(true),
  speed_(speed) {
  navi_.Reroute(origin, terminus);
}

void Walker::Update(float elapsed_time) {
  if (glm::distance(pos(), goal_->pos()) <= 0.1f) {
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
    glm::vec2 movedir = glm::normalize(goal_->pos() - pos());
    set_pos(pos() + movedir * speed_ * elapsed_time);
    set_rot(glm::atan(movedir.y, movedir.x) + glm::radians(90.0f));
  }
}

void Walker::Reroute(const Waypoint &terminus) {
  navi_.Reroute(*goal_, terminus);
}

void Walker::Draw() {
  glm::vec3 color;
  if (CheckStatus() == kWalkerRerouting) {
    glColor3ubv(kYellowColor);
  } else if (CheckStatus() == kWalkerMoving) {
    glColor3ubv(kGreenColor);
  } else {
    glColor3ubv(kBlueColor);
  }
  RectangleEntity::Draw();

  if (goal_ != nullptr) {
    glColor3ubv(kYellowColor);
    glBegin(GL_LINE_LOOP);
    glVertex2fv(glm::value_ptr(pos()));
    glVertex2fv(glm::value_ptr(goal_->pos()));
    glEnd();
  }
  const Waypoint *terminus = navi_.GetTerminus();
  if (terminus != nullptr) {
    glColor3ubv(kRedColor);
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
