/**
 * Copyright (C) 2014 The Motel On Jupiter
 */

#include <cassert>
#include <boost/foreach.hpp>

inline int Walker::BuildTravelListImpl(const Waypoint *point, const Waypoint *finalgoal, std::vector<const Waypoint *> &breadcrumbs, std::vector<const Waypoint *> **minlist) {
  assert(minlist != nullptr);

  // For short circuit
  if ((*minlist != nullptr) && (breadcrumbs.size() + 2 >= (*minlist)->size())) {
    return 0;
  }

  // Detect the looping
  BOOST_FOREACH(auto breadcrumb, breadcrumbs) {
    if (point == breadcrumb) {
      return 0;
    }
  }

  BOOST_FOREACH(auto nextpoint, point->nextpoints()) {
    // Check whether this node is goal or not
    if (nextpoint == finalgoal) {
      if ((*minlist == nullptr) ||
          (breadcrumbs.size() + 2 < (*minlist)->size())) {
        delete *minlist;
        *minlist = new std::vector<const Waypoint *>(breadcrumbs);
        if (minlist == nullptr) {
          return -1;
        }
        (*minlist)->push_back(nextpoint);
        (*minlist)->push_back(finalgoal);
      }
      return 0;
    }

    // Walk the next nodes
    breadcrumbs.push_back(point);
    if (BuildTravelListImpl(nextpoint, finalgoal, breadcrumbs, minlist) < 0) {
      return -1;
    }
    breadcrumbs.pop_back();
  }
  return 0;
}
