/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#ifndef ENTITYPHISIOLOGY_H_
#define ENTITYPHISIOLOGY_H_

#include "entity/BaseEntity.h"

class EntityPhisiology : public EntityMixIn {
 public:
  EntityPhisiology(BaseEntity &entity);
  virtual ~EntityPhisiology() {}

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

#endif /* ENTITYPHISIOLOGY_H_ */
