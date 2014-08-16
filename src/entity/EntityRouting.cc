/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "entity/EntityRouting.h"
#include "entity/BaseEntity.h"

EntityRouting::EntityRouting(BaseEntity &entity, const WaypointGraph &graph,
                             const Waypoint &origin, const Waypoint &terminus,
                             float speed) :
  EntityMixIn(entity),
  navi_(graph),
  goal_(&origin),
  reached_(true),
  speed_(speed) {
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
    float movedirangle = glm::atan(movedir.y, movedir.x) + glm::radians(90.0f);
    float diffangle = movedirangle - entity().rot();
    float diffangleabs = abs(diffangle);
    if (diffangleabs < FLT_EPSILON) {
      entity().set_pos(entity().pos() + movedir * speed_ * elapsed_time);
    } else {
      float diffanglesign = static_cast<float>((diffangle > 0) - (diffangle < 0));
      float newrot = entity().rot() + std::min<float>(0.1f, diffangleabs) * diffanglesign;
      entity().set_rot(newrot);
    }
  }
}

void EntityRouting::Reroute(const Waypoint &terminus) {
  navi_.Reroute(*goal_, terminus);
}

