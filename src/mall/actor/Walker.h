/**
 * Copyright (C) 2014 The Motel On Jupiter
 */

#ifndef WALKER_H_
#define WALKER_H_

#include <boost/noncopyable.hpp>
#include "mall/actor/Entity.h"
#include "navigation/Waypoint.h"

class SimpleWalker : public RectangleEntity {
 public:
  SimpleWalker(const Waypoint &start);
  virtual ~SimpleWalker() {}

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

class Walker : public SimpleWalker, private boost::noncopyable {
public:
  Walker(const Waypoint &start, const WaypointGraph &graph);
  virtual ~Walker();

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

class RandomWalker : public SimpleWalker, private boost::noncopyable {
public:
  RandomWalker(const Waypoint &start, const WaypointGraph &graph);

  virtual void SelectNextGoal(const Waypoint *current_goal);

protected:
  virtual bool arrived() const { return SimpleWalker::arrived(); }

private:
  const WaypointGraph &graph_;
};

#include "mall/actor/Walker.inl"

#endif /* WALKER_H_ */
