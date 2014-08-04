/**
 * Copyright (C) 2014 The Motel On Jupiter
 */

#include <cassert>
#include <boost/foreach.hpp>

inline int NodeGraphWalker::BuildTravelNodeListImpl(const WalkNode *curnode, const WalkNode *finalgoal, std::vector<const WalkNode *> &breadcrumbs, std::vector<const WalkNode *> **minlist) {
  assert(minlist != nullptr);

  // For short circuit
  if ((*minlist != nullptr) && (breadcrumbs.size() + 2 >= (*minlist)->size())) {
    return 0;
  }

  // Detect the looping
  BOOST_FOREACH(auto breadcrumb, breadcrumbs) {
    if (curnode == breadcrumb) {
      return 0;
    }
  }

  BOOST_FOREACH(auto nextnode, curnode->nextnodes()) {
    // Check whether this node is goal or not
    if (nextnode == finalgoal) {
      if ((*minlist == nullptr) ||
          (breadcrumbs.size() + 2 < (*minlist)->size())) {
        delete *minlist;
        *minlist = new std::vector<const WalkNode *>(breadcrumbs);
        if (minlist == nullptr) {
          return -1;
        }
        (*minlist)->push_back(nextnode);
        (*minlist)->push_back(finalgoal);
      }
      return 0;
    }

    // Walk the next nodes
    breadcrumbs.push_back(curnode);
    if (BuildTravelNodeListImpl(nextnode, finalgoal, breadcrumbs, minlist) < 0) {
      return -1;
    }
    breadcrumbs.pop_back();
  }
  return 0;
}
