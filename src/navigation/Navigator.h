/**
 * Copyright (C) 2014 The Motel on Jupiter
 */

#ifndef NAVIGATOR_H_
#define NAVIGATOR_H_

#include <cassert>
#include <deque>
#include <future>
#include <boost/foreach.hpp>
#include <boost/noncopyable.hpp>
#include "navigation/Waypoint.h"

class Navigator : private boost::noncopyable {
public:
  explicit Navigator(const WaypointGraph &graph);
  virtual ~Navigator();

  const Waypoint *NextGoal();
  void Reroute(const Waypoint &origin, const Waypoint &terminus);
  const Waypoint *GetTerminus() const;

  bool rerouting() const { return rerouting_; }

private:
  static int BuildRouteImpl(const Waypoint *transfer, const Waypoint *terminus, std::deque<const Waypoint *> &traceroute, std::deque<const Waypoint *> &bestroute, bool &abortion);
  static int BuildRoute(const Waypoint *transfer, const Waypoint *terminus, std::deque<const Waypoint *> *route, bool *abortion);

  const WaypointGraph &graph_;
  std::deque<const Waypoint *> routepath_;
  std::future<int> reroute_;
  bool rerouting_;
  std::deque<const Waypoint *> reroutepath_;
  bool reroutingabortion_;
};

inline int Navigator::BuildRouteImpl(const Waypoint *transfer, const Waypoint *terminus, std::deque<const Waypoint *> &traceroute, std::deque<const Waypoint *> &bestroute, bool &abortion) {
  // Detect the abortion
  if (abortion) {
    return 1;
  }

  // For short circuit
  if ((bestroute.size() != 0) && (traceroute.size() + 3 >= bestroute.size())) {
    return 0;
  }

  // Detect the looping
  BOOST_FOREACH(auto trace, traceroute) {
    if (transfer == trace) {
      return 0;
    }
  }

  BOOST_FOREACH(auto nextpoint, transfer->nextpoints()) {
    // Detect the abortion
    if (abortion) {
      return 1;
    }

    // Check whether this node is goal or not
    if (nextpoint == terminus) {
      if ((bestroute.size() == 0) ||
          (traceroute.size() + 3 < bestroute.size())) {
        bestroute = traceroute;
        bestroute.push_back(transfer);
        bestroute.push_back(nextpoint);
        bestroute.push_back(terminus);
      }
      return 0;
    }

    // Walk the next nodes
    traceroute.push_back(transfer);
    if (BuildRouteImpl(nextpoint, terminus, traceroute, bestroute, abortion) < 0) {
      return -1;
    }
    traceroute.pop_back();
  }
  return 0;
}

#endif /* NAVIGATOR_H_ */
