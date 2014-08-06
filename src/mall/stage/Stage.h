/**
 * Copyright (C) 2014 The Motel On Jupiter
 */

#ifndef STAGE_H_
#define STAGE_H_

#include "navigation/Waypoint.h"

class Stage {
public:
  Stage();
  virtual ~Stage();

  virtual int Initialize(const glm::vec2 &window_size) = 0;
  virtual void Finalize() = 0;

  void Draw(const glm::vec2 &window_size);

  const WaypointGraph& const_graph() const { return graph_; }

protected:
  WaypointGraph& graph() { return graph_; }

private:
  WaypointGraph graph_;
};

class GridStage : public Stage {
 public:
  static const float kGridInterval;

  GridStage();
  virtual ~GridStage();

  virtual int Initialize(const glm::vec2 &window_size);
  virtual void Finalize();
};

class RoughGridStage : public GridStage {
 public:
  RoughGridStage();
  virtual ~RoughGridStage();

  virtual int Initialize(const glm::vec2 &window_size);
};

#endif /* STAGE_H_ */
