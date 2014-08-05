/**
 * Copyright (C) 2014 The Motel On Jupiter
 */

#ifndef NAVIGATOR_H_
#define NAVIGATOR_H_

#include <cassert>
#include <deque>
#include <boost/foreach.hpp>
#include <boost/noncopyable.hpp>
#include "navigation/Waypoint.h"

class Navigator : private boost::noncopyable {
public:
  Navigator(const WaypointGraph &graph);
  virtual ~Navigator();

  const Waypoint *NextGoal();
  int UpdateRoute(const Waypoint &origin, const Waypoint &terminus);

  const Waypoint *terminus() const { return terminus_; }

private:
  int BuildRoute(const Waypoint *transfer, const Waypoint *terminus, std::deque<const Waypoint *> &traceroute, std::deque<const Waypoint *> &bestroute);

  const WaypointGraph &graph_;
  std::deque<const Waypoint *> route_;
  const Waypoint *terminus_;
};

inline int Navigator::BuildRoute(const Waypoint *transfer, const Waypoint *terminus, std::deque<const Waypoint *> &traceroute, std::deque<const Waypoint *> &bestroute) {
  // For short circuit
  if ((bestroute.size() != 0) && (traceroute.size() + 2 >= bestroute.size())) {
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
          (traceroute.size() + 2 < bestroute.size())) {
        bestroute = traceroute;
        bestroute.push_back(nextpoint);
        bestroute.push_back(terminus);
      }
      return 0;
    }

    // Walk the next nodes
    traceroute.push_back(transfer);
    if (BuildRoute(nextpoint, terminus, traceroute, bestroute) < 0) {
      return -1;
    }
    traceroute.pop_back();
  }
  return 0;
}

#endif /* NAVIGATOR_H_ */
