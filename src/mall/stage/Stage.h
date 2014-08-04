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

  virtual int Initialize(const glm::vec2 &window_size);
  virtual void Finalize();
  virtual void Draw(const glm::vec2 &window_size);

  const WalkNodeMap& nodemap() const { return nodemap_; }

private:
  WalkNodeMap nodemap_;
};

#endif /* STAGE_H_ */
