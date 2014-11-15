/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#ifndef CORE_ACTOR_MOUSE_H_
#define CORE_ACTOR_MOUSE_H_

#include <vector>
#include "mojgame/catalogue/entity_extention/PlanarEntityDraw.h"
#include "mojgame/entity/PlanarEntity.h"

class MouseCheese;
class MouseFood;
class MouseWater;

class MousePhisiology : public mojgame::PlanarEntityExtention {
 public:
  MousePhisiology(mojgame::PlanarEntity &entity);
  virtual ~MousePhisiology() {
  }

  virtual void Update(float elapsed_time);

  float GetAppetiteForFood() const;
  float GetAppetiteForDrink() const;
  float GetDesireForSleep() const;
  void GratifyAppetitleForFood(float degree);
  void GratifyAppetitleForDrink(float degree);
  void GratifyDesireForSleep(float degree);

 private:
  float hungry_;
  float maxhungry_;
  float thirsty_;
  float maxthirsty_;
  float sleepy_;
  float maxsleepy_;
};

class Mouse : public mojgame::PlanarEntity, public mojgame::EntityTriangleDraw,
    public MousePhisiology {
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

#endif /* CORE_ACTOR_MOUSE_H_ */
