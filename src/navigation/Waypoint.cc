/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "navigation/Waypoint.h"
#include <boost/foreach.hpp>
#include "util/logging/Logger.h"

Waypoint::Waypoint(const glm::vec2 &pos) :
  pos_(pos), nextpoints_() {
}

void Waypoint::AddNextPoint(Waypoint *point) {
  nextpoints_.push_back(point);
}

WaypointGraph::WaypointGraph() : points_() {
}

WaypointGraph::~WaypointGraph() {
}

void WaypointGraph::AddPoint(Waypoint *point) {
  points_.push_back(point);
}

void WaypointGraph::Clear() {
  BOOST_FOREACH(auto point, points_) {
    delete point;
  }
  points_.clear();
}


const Waypoint *WaypointGraph::CalcNearestPoint(const glm::vec2 &pos) const {
  const Waypoint *nearest = nullptr;
  float nearest_len = FLT_MAX;
  BOOST_FOREACH(auto point, points_) {
    float len = glm::length(point->pos() - pos);
    if (len < nearest_len) {
      nearest = point;
      nearest_len = len;
    }
  }
  return nearest;
}
