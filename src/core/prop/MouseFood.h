/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#ifndef CORE_PROP_MOUSEFOOD_H_
#define CORE_PROP_MOUSEFOOD_H_

#include "mojgame/catalogue/entity_extention/PlanarEntityDraw.h"
#include "mojgame/entity/PlanarEntity.h"
#include "mojgame/includer/glm_include.h"

class Mouse;

class MouseFood : public mojgame::PlanarEntity,
    public mojgame::EntityRectangleDraw {
 public:
  MouseFood(const glm::vec2 &pos, float rot, const glm::vec2 &scale,
            const GLubyte *color);
  virtual ~MouseFood();

  virtual void Affect(Mouse &mouse) const = 0;
};

class MouseCheese : public MouseFood {
 public:
  MouseCheese(const glm::vec2 &pos, float rot, const glm::vec2 &scale);
  virtual ~MouseCheese();

  virtual void Affect(Mouse &mouse) const;
};

class MouseWater : public MouseFood {
 public:
  MouseWater(const glm::vec2 &pos, float rot, const glm::vec2 &scale);
  virtual ~MouseWater();

  virtual void Affect(Mouse &mouse) const;
};

#endif /* CORE_PROP_MOUSEFOOD_H_ */
