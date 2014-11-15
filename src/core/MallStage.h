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

  virtual int Initialize(const glm::vec2 &size);
  virtual void Finalize() = 0;

  void Draw();

  const WaypointGraph &const_graph() const { return graph_; }
  const glm::vec2 &size() const { return size_; }

protected:
  WaypointGraph& graph() { return graph_; }

private:
  glm::vec2 size_;
  WaypointGraph graph_;
};

#endif /* MALLSTAGE_H_ */
