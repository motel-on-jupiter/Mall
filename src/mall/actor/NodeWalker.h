/**
 * Copyright (C) 2014 The Motel On Jupiter
 */

#ifndef NODEWALKER_H_
#define NODEWALKER_H_

#include <boost/noncopyable.hpp>
#include "mall/actor/Entity.h"
#include "navigation/Waypoint.h"

class NodeWalker : public RectangleEntity {
 public:
  NodeWalker(const Waypoint &start);
  virtual ~NodeWalker() {}

  virtual void Update();
  void SetGoal(const Waypoint *goal) { goal_ = goal; arrived_ = false; }
  virtual void DrawApproach(const glm::vec2 &window_size);

  virtual bool arrived() const { return arrived_; }

  const Waypoint* goal() const { return goal_; }

 protected:
  virtual void SelectNextGoal(const Waypoint *current_goal);

 private:
  const Waypoint *goal_;
  bool arrived_;
};

class NodeGraphWalker : public NodeWalker, private boost::noncopyable {
public:
  NodeGraphWalker(const Waypoint &start, const WaypointGraph &graph);
  virtual ~NodeGraphWalker();

  int UpdateFinalGoal(const Waypoint *finalgoal);
  virtual void DrawApproach(const glm::vec2 &window_size);

protected:
  virtual void SelectNextGoal(const Waypoint *current_goal);

private:
  int BuildTravelListImpl(const Waypoint *point, const Waypoint *finalgoal, std::vector<const Waypoint *> &breadcrumbs, std::vector<const Waypoint *> **minlist);
  int BuildTravelList(const Waypoint *finalgoal);

  const WaypointGraph &graph_;
  std::vector<const Waypoint *> *travellist_;
  const Waypoint *finalgoal_;
};

class RandomNodeGraphWalker : public NodeWalker, private boost::noncopyable {
public:
  RandomNodeGraphWalker(const Waypoint &start, const WaypointGraph &graph);

  virtual void SelectNextGoal(const Waypoint *current_goal);

protected:
  virtual bool arrived() const { return NodeWalker::arrived(); }

private:
  const WaypointGraph &graph_;
};

#include "mall/actor/NodeWalker.inl"

#endif /* NODEWALKER_H_ */
