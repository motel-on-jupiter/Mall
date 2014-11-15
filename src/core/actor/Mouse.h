/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#ifndef MOUSE_H_
#define MOUSE_H_

#include <vector>
#include "entity/BaseEntity.h"
#include "entity/EntityDraw.h"
#include "entity/EntityPhisiology.h"

class MouseCheese;
class MouseFood;
class MouseWater;

class Mouse :
    public BaseEntity, public EntityTriangleDraw, public EntityPhisiology {
 public:
  Mouse(const glm::vec2 &pos, float rot, const glm::vec2 &scale,
        const std::vector<const MouseCheese *> &cheeses,
        const std::vector<const MouseWater *> &waters);
  virtual ~Mouse();

  virtual void Update(float elapsed_time);

 private:
  enum State {
    kIdle,
    kTargeting,
    kIngesting,
  };

  const std::vector<const MouseCheese *> &cheeses_;
  const std::vector<const MouseWater *> &waters_;
  State state_;
  const MouseFood *target_;
  float ingestingtimer_;
};

#endif /* MOUSE_H_ */
