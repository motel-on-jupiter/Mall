/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#ifndef ENTITYROUTING_H_
#define ENTITYROUTING_H_

#include "entity/BaseEntity.h"
#include "navigation/Navigator.h"

class EntityRouting : public EntityMixIn {
public:
  EntityRouting(BaseEntity &entity, const WaypointGraph &graph,
                const Waypoint &origin, const Waypoint &terminus,
                float movespeed, float turnspeed);
  ~EntityRouting() {}

  void Update(float elapsed_time);
  void Reroute(const Waypoint &terminus);

  Navigator &navi() { return navi_; }
  bool reached() const { return reached_; }
  float movespeed() const { return movespeed_; }
  float turnspeed() const { return turnspeed_; }

protected:
  const Waypoint *goal() const { return goal_; }

private:
  Navigator navi_;
  const Waypoint *goal_;
  bool reached_;
  float movespeed_;
  float turnspeed_;
};

#endif /* ENTITYROUTING_H_ */
