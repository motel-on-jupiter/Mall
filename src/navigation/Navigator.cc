/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "navigation/Navigator.h"
#include "util/logging/Logger.h"
#include "util/macro_util.h"

Navigator::Navigator(const WaypointGraph &graph) :
  graph_(graph), route_(), terminus_(nullptr) {
}

Navigator::~Navigator() {
}

const Waypoint *Navigator::NextGoal() {
  if (route_.size() == 0) {
    return nullptr;
  }
  const Waypoint *next = route_.front();
  route_.pop_front();
  return next;
}

int Navigator::UpdateRoute(const Waypoint &origin, const Waypoint &terminus) {
  std::deque<const Waypoint *> traceroute;
  std::deque<const Waypoint *> bestroute;
  int ret = BuildRoute(&origin, &terminus, traceroute, bestroute);
  if (ret < 0) {
    LOGGER.Error("Failed to build route (ret: %d)", ret);
    return -1;
  }
  route_ = bestroute;
  terminus_ = &terminus;
  return 0;
}
