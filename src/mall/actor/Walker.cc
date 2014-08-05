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
  RectangleEntity(origin.pos(), glm::vec2(5.0f, 5.0f)), navi_(graph), goal_() {
  int ret = navi_.UpdateRoute(origin, terminus);
  if (ret < 0) {
    LOGGER.Warn("Failed to build the walker route (ret: %d)", ret);
    return;
  }
}

void Walker::Update() {
  if (goal_ == nullptr) {
    goal_ = navi_.NextGoal();
  }
  if (goal_ == nullptr) {
    return;
  }
  if (glm::distance(pos(), goal_->pos()) <= 1.0f) {
    set_pos(goal_->pos());
    goal_ = navi_.NextGoal();
  } else {
    set_pos(pos() + glm::normalize(goal_->pos() - pos()));
  }
}

int Walker::Reroute(const Waypoint &terminus) {
  return navi_.UpdateRoute(*goal_, terminus);
}

void Walker::DrawApproach(const glm::vec2 &window_size) {
  if (goal_ != nullptr) {
    glColor3fv(glm::value_ptr(kYellowColor));
    glBegin(GL_LINE_LOOP);
    glVertex2f(pos().x / window_size.x * 2.0f - 1.0f, pos().y / window_size.y * 2.0f - 1.0f);
    glVertex2f(goal_->pos().x / window_size.x * 2.0f - 1.0f, goal_->pos().y / window_size.y * 2.0f - 1.0f);
    glEnd();
  }
  if (navi_.terminus() != nullptr) {
    glColor3fv(glm::value_ptr(kRedColor));
    glBegin(GL_LINE_LOOP);
    glVertex2f(pos().x / window_size.x * 2.0f - 1.0f, pos().y / window_size.y * 2.0f - 1.0f);
    glVertex2f(navi_.terminus()->pos().x / window_size.x * 2.0f - 1.0f, navi_.terminus()->pos().y / window_size.y * 2.0f - 1.0f);
    glEnd();
  }
}

Walker::WalkerStatus Walker::CheckStatus() const {
  if (goal_ == nullptr) {
    return kWalkerStandBy;
  }
  return kWalkerMoving;
}
