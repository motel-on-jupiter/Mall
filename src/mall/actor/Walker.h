/**
 * Copyright (C) 2014 The Motel On Jupiter
 */

#ifndef WALKER_H_
#define WALKER_H_

#include "mall/actor/Entity.h"
#include "navigation/Navigator.h"

class Walker : public RectangleEntity {
public:
  Walker(const WaypointGraph &graph, const Waypoint &origin, const Waypoint &terminus);
  virtual ~Walker() {}

  void Update();
  int Reroute(const Waypoint &terminus);
  void DrawApproach(const glm::vec2 &window_size);

private:
  Navigator navi_;
  const Waypoint *goal_;
};

#endif /* WALKER_H_ */
