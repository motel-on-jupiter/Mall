/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "entity/EntityRouting.h"
#include "entity/BaseEntity.h"

EntityRouting::EntityRouting(BaseEntity &entity, const WaypointGraph &graph,
                             const Waypoint &origin, const Waypoint &terminus,
                             float speed) :
  entity_(entity),
  navi_(graph),
  goal_(&origin),
  reached_(true),
  speed_(speed) {
  navi_.Reroute(origin, terminus);
}

void EntityRouting::Update(float elapsed_time) {
  if (glm::distance(entity_.pos(), goal_->pos()) <= 0.1f) {
    entity_.set_pos(goal_->pos());
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
    glm::vec2 movedir = glm::normalize(goal_->pos() - entity_.pos());
    entity_.set_pos(entity_.pos() + movedir * speed_ * elapsed_time);
    entity_.set_rot(glm::atan(movedir.y, movedir.x) + glm::radians(90.0f));
  }
}

void EntityRouting::Reroute(const Waypoint &terminus) {
  navi_.Reroute(*goal_, terminus);
}

