/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#ifndef MOUSEFOOD_H_
#define MOUSEFOOD_H_

#include "entity/BaseEntity.h"
#include "entity/EntityDraw.h"

class MouseFood : public BaseEntity, public EntityRectangleDraw {
 public:
  MouseFood(const glm::vec2 &pos, float rot, const glm::vec2 &scale);
  virtual ~MouseFood();

  virtual void Draw();
};

#endif /* MOUSEFOOD_H_ */
