/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include <algorithm>
#include "EntityPhisiology.h"
#include "util/math_aux.h"

EntityPhisiology::EntityPhisiology(BaseEntity &entity)
: EntityMixIn(entity),
  hungry_(0.0f), maxhungry_(100.0f),
  thirsty_(0.0f), maxthirsty_(100.0f),
  sleepy_(0.0f), maxsleepy_(100.0f) {
}

void EntityPhisiology::Update(float elapsed_time) {
  hungry_ = std::min(hungry_ + 0.01f * elapsed_time, maxhungry_);
  thirsty_ = std::min(thirsty_ + 0.01f * elapsed_time, maxthirsty_);
  sleepy_ = std::min(sleepy_ + 0.003f * elapsed_time, maxsleepy_);
}

float EntityPhisiology::GetAppetiteForFood() const {
  return is_fzero(maxhungry_) ? 1.0f : hungry_ / maxhungry_;
}

float EntityPhisiology::GetAppetiteForDrink() const {
  return is_fzero(maxthirsty_) ? 1.0f : thirsty_ / maxthirsty_;
}

float EntityPhisiology::GetDesireForSleep() const {
  return is_fzero(maxsleepy_) ? 1.0f : sleepy_ / maxsleepy_;
}

void EntityPhisiology::GratifyAppetitleForFood(float degree) {
  hungry_ = std::max(hungry_ - degree, 0.0f);
}

void EntityPhisiology::GratifyAppetitleForDrink(float degree) {
  thirsty_ = std::max(thirsty_ - degree, 0.0f);
}

void EntityPhisiology::GratifyDesireForSleep(float degree) {
  sleepy_ = std::max(sleepy_ - degree, 0.0f);
}
