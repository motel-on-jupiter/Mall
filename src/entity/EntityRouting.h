/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#ifndef ENTITYROUTING_H_
#define ENTITYROUTING_H_

#include "navigation/Navigator.h"

class BaseEntity;

class EntityRouting {
public:
  EntityRouting(BaseEntity &entity, const WaypointGraph &graph,
                     const Waypoint &origin, const Waypoint &terminus,
                     float speed);
  ~EntityRouting() {}

  void Update(float elapsed_time);
  void Reroute(const Waypoint &terminus);

  Navigator &navi() { return navi_; }
  bool reached() const { return reached_; }
  float speed() const { return speed_; }

protected:
  const Waypoint *goal() const { return goal_; }

private:
  BaseEntity &entity_;
  Navigator navi_;
  const Waypoint *goal_;
  bool reached_;
  float speed_;
};

#endif /* ENTITYROUTING_H_ */
