/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#ifndef MOUSE_H_
#define MOUSE_H_

#include "entity/BaseEntity.h"
#include "entity/EntityDraw.h"

class Mouse : public BaseEntity, public EntityTriangleDraw {
 public:
  Mouse(const glm::vec2 &pos, float rot, const glm::vec2 &scale);
  virtual ~Mouse();
};

#endif /* MOUSE_H_ */
