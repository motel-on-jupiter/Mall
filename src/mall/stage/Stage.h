/**
 * Copyright (C) 2014 The Motel On Jupiter
 */

#ifndef STAGE_H_
#define STAGE_H_

#include "mall/actor/WalkNode.h"

class Stage {
public:
  Stage();
  virtual ~Stage();

  virtual int Initialize(const glm::vec2 &window_size) = 0;
  virtual void Finalize() = 0;

  void Draw(const glm::vec2 &window_size);

  const WalkNodeGraph& const_graph() const { return nodemap_; }

protected:
  WalkNodeGraph& nodemap() { return nodemap_; }

private:
  WalkNodeGraph nodemap_;
};

class GridStage : public Stage {
 public:
  static const float kMapNodeInterval;

  GridStage();
  virtual ~GridStage();

  virtual int Initialize(const glm::vec2 &window_size);
  virtual void Finalize();
};


#endif /* STAGE_H_ */
