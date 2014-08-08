/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "navigation/Navigator.h"
#include "util/logging/Logger.h"
#include "util/macro_util.h"

Navigator::Navigator(const WaypointGraph &graph) :
  graph_(graph), routepath_(), reroute_(), rerouting_(false),reroutepath_() {
}

Navigator::~Navigator() {
}

const Waypoint *Navigator::NextGoal() {
  if (rerouting_) {
    if (reroute_.valid() &&
        std::future_status::ready == reroute_.wait_for(std::chrono::microseconds(1))) {
      rerouting_ = false;
      routepath_ = reroutepath_;
    }
    else {
      return nullptr;
    }
  }
  if (routepath_.size() == 0) {
    return nullptr;
  }
  const Waypoint *next = routepath_.front();
  routepath_.pop_front();
  return next;
}

void Navigator::Reroute(const Waypoint &origin, const Waypoint &terminus) {
  reroute_ = std::async(std::launch::async, BuildRoute, &origin, &terminus, &reroutepath_);
  rerouting_ = true;
}

const Waypoint *Navigator::GetTerminus() const {
  if (routepath_.size() == 0) {
    return nullptr;
  }
  return routepath_.back();
}

int Navigator::BuildRoute(const Waypoint *tranfer, const Waypoint *terminus, std::deque<const Waypoint *> *route) {
  std::deque<const Waypoint *> traceroute;
  std::deque<const Waypoint *> bestroute;
  int ret = BuildRouteImpl(tranfer, terminus, traceroute, bestroute);
  if (ret < 0) {
    LOGGER.Error("Failed to build route (ret: %d)", ret);
    return -1;
  }
  *route = bestroute;
  return 0;
}
