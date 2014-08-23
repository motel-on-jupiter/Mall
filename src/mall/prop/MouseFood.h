/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#ifndef MOUSEFOOD_H_
#define MOUSEFOOD_H_

#include "entity/BaseEntity.h"
#include "entity/EntityDraw.h"

class MouseFood : public BaseEntity, public EntityRectangleDraw {
 public:
  MouseFood(const glm::vec2 &pos, float rot, const glm::vec2 &scale, const GLubyte *color);
  virtual ~MouseFood();
};

class MouseCheese : public MouseFood {
 public:
  MouseCheese(const glm::vec2 &pos, float rot, const glm::vec2 &scale);
  virtual ~MouseCheese();
};

class MouseWater : public MouseFood {
 public:
  MouseWater(const glm::vec2 &pos, float rot, const glm::vec2 &scale);
  virtual ~MouseWater();
};

#endif /* MOUSEFOOD_H_ */
