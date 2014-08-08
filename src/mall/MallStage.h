/**
 * Copyright (C) 2014 The Motel on Jupiter
 */

#ifndef MALLSTAGE_H_
#define MALLSTAGE_H_

#include "navigation/Waypoint.h"

class MallStage {
public:
  MallStage();
  virtual ~MallStage();

  virtual int Initialize(const glm::vec2 &window_size) = 0;
  virtual void Finalize() = 0;

  void Draw(const glm::vec2 &window_size);

  const WaypointGraph& const_graph() const { return graph_; }

protected:
  WaypointGraph& graph() { return graph_; }

private:
  WaypointGraph graph_;
};

#endif /* MALLSTAGE_H_ */
