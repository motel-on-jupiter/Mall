/**
 * Copyright (C) 2014 The Motel On Jupiter
 */

#ifndef WAYPOINT_H_
#define WAYPOINT_H_

#include <vector>

class Waypoint {
public:
  Waypoint(const glm::vec2 &pos);
  virtual ~Waypoint() {}

  void AddNextPoint(Waypoint *point);
  int RemoveNextPoint(Waypoint *point);

  const glm::vec2& pos() const { return pos_; }
  const std::vector<Waypoint*>& nextpoints() const { return nextpoints_; }

private:
  glm::vec2 pos_;
  std::vector<Waypoint *> nextpoints_;
};

class WaypointGraph {
 public:
  WaypointGraph();
  ~WaypointGraph();

  int Initialize(const glm::vec2 &window_size);
  void Finalize();

  void AddPoint(Waypoint *point);
  void Clear();

  const Waypoint *CalcNearestPoint (const glm::vec2 &pos) const ;

  const std::vector<Waypoint*>& points() const { return points_; }

 private:
  std::vector<Waypoint *> points_;
};

#endif /* WAYPOINT_H_ */
