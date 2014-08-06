/**
 * Copyright (C) 2014 The Motel On Jupiter
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
  Navigator(const WaypointGraph &graph);
  virtual ~Navigator();

  const Waypoint *NextGoal();
  void Reroute(const Waypoint &origin, const Waypoint &terminus);
  const Waypoint *GetTerminus() const;

  bool rerouting() const { return rerouting_; }

private:
  static int BuildRouteImpl(const Waypoint *transfer, const Waypoint *terminus, std::deque<const Waypoint *> &traceroute, std::deque<const Waypoint *> &bestroute);
  static int BuildRoute(const Waypoint *transfer, const Waypoint *terminus, std::deque<const Waypoint *> *route);

  const WaypointGraph &graph_;
  std::deque<const Waypoint *> routepath_;
  std::future<int> reroute_;
  bool rerouting_;
  std::deque<const Waypoint *> reroutepath_;
};

inline int Navigator::BuildRouteImpl(const Waypoint *transfer, const Waypoint *terminus, std::deque<const Waypoint *> &traceroute, std::deque<const Waypoint *> &bestroute) {
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
    if (BuildRouteImpl(nextpoint, terminus, traceroute, bestroute) < 0) {
      return -1;
    }
    traceroute.pop_back();
  }
  return 0;
}

#endif /* NAVIGATOR_H_ */
