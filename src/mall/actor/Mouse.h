/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#ifndef MOUSE_H_
#define MOUSE_H_

#include <vector>
#include "entity/BaseEntity.h"
#include "entity/EntityDraw.h"
#include "entity/EntityPhisiology.h"

class MouseFood;

class Mouse :
    public BaseEntity, public EntityTriangleDraw, public EntityPhisiology {
 public:
  Mouse(const glm::vec2 &pos, float rot, const glm::vec2 &scale,
        std::vector<const MouseFood *> &foods);
  virtual ~Mouse();

  virtual void Update(float elapsed_time);

 private:
  std::vector<const MouseFood *> foods_;
  std::vector<const MouseFood *>::iterator target_;
  float ingestingtimer_;
};

#endif /* MOUSE_H_ */
