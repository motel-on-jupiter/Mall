/**
 * Copyright (C) 2014 The Motel on Jupiter
 */

#ifndef CORE_MALLSTAGE_H_
#define CORE_MALLSTAGE_H_

#include "mojgame/navigation/Waypoint.h"

class MallStage {
public:
  MallStage();
  virtual ~MallStage();

  virtual int Initialize(const glm::vec2 &size);
  virtual void Finalize() = 0;

  void Draw();

  const mojgame::WaypointGraph &const_graph() const { return graph_; }
  const glm::vec2 &size() const { return size_; }

protected:
  mojgame::WaypointGraph& graph() { return graph_; }

private:
  glm::vec2 size_;
  mojgame::WaypointGraph graph_;
};

#endif /* CORE_MALLSTAGE_H_ */
