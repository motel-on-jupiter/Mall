/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "entity/EntityRouting.h"
#include "entity/BaseEntity.h"
#include "util/math_aux.h"

EntityRouting::EntityRouting(BaseEntity &entity, const WaypointGraph &graph,
                             const Waypoint &origin, const Waypoint &terminus,
                             float speed, float turnspeed) :
  EntityMixIn(entity),
  navi_(graph),
  goal_(&origin),
  reached_(true),
  movespeed_(speed),
  turnspeed_(turnspeed) {
  navi_.Reroute(origin, terminus);
}

void EntityRouting::Update(float elapsed_time) {
  if (glm::distance(entity().pos(), goal_->pos()) <= 0.1f) {
    entity().set_pos(goal_->pos());
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
    glm::vec2 movedir = glm::normalize(goal_->pos() - entity().pos());
    float movedirangle = normalize_angle(atan2(movedir.y, movedir.x) +
                                         glm::radians(90.0f));
    float diffangle = normalize_angle(movedirangle - entity().rot());
    if (abs(diffangle) < FLT_EPSILON) {
      entity().set_pos(entity().pos() + movedir * movespeed_ * elapsed_time);
    } else {
      float invdiffangle = normalize_angle(entity().rot() - movedirangle);
      if (abs(diffangle) > abs(invdiffangle)) {
        diffangle = invdiffangle;
      }
      entity().set_rot(normalize_angle(entity().rot() +
                                       std::min<float>(turnspeed_, abs(diffangle)) *
                                       sign_f(diffangle)));
    }
  }
}

void EntityRouting::Reroute(const Waypoint &terminus) {
  navi_.Reroute(*goal_, terminus);
}

