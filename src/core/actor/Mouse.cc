/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "core/actor/Mouse.h"
#include <algorithm>
#include "core/prop/MouseFood.h"
#include "mojgame/auxiliary/math_aux.h"
#include "mojgame/sampler/color_sample.h"

MousePhisiology::MousePhisiology(mojgame::PlanarEntity &entity)
    : mojgame::PlanarEntityExtention(entity),
      hungry_(0.0f),
      maxhungry_(100.0f),
      thirsty_(0.0f),
      maxthirsty_(100.0f),
      sleepy_(0.0f),
      maxsleepy_(100.0f) {
}

void MousePhisiology::Update(float elapsed_time) {
  hungry_ = std::min(hungry_ + 10.0f * elapsed_time, maxhungry_);
  thirsty_ = std::min(thirsty_ + 10.0f * elapsed_time, maxthirsty_);
  sleepy_ = std::min(sleepy_ + 3.0f * elapsed_time, maxsleepy_);
}

float MousePhisiology::GetAppetiteForFood() const {
  return mojgame::math_aux::is_fzero(maxhungry_) ? 1.0f : hungry_ / maxhungry_;
}

float MousePhisiology::GetAppetiteForDrink() const {
  return
      mojgame::math_aux::is_fzero(maxthirsty_) ? 1.0f : thirsty_ / maxthirsty_;
}

float MousePhisiology::GetDesireForSleep() const {
  return mojgame::math_aux::is_fzero(maxsleepy_) ? 1.0f : sleepy_ / maxsleepy_;
}

void MousePhisiology::GratifyAppetitleForFood(float degree) {
  hungry_ = std::max(hungry_ - degree, 0.0f);
}

void MousePhisiology::GratifyAppetitleForDrink(float degree) {
  thirsty_ = std::max(thirsty_ - degree, 0.0f);
}

void MousePhisiology::GratifyDesireForSleep(float degree) {
  sleepy_ = std::max(sleepy_ - degree, 0.0f);
}

Mouse::Mouse(const glm::vec2 &pos, float rot, const glm::vec2 &scale,
             const std::vector<const MouseCheese *> &cheeses,
             const std::vector<const MouseWater *> &waters)
    : mojgame::PlanarEntity(pos, rot, scale),
      mojgame::EntityTriangleDraw(*(static_cast<mojgame::PlanarEntity *>(this)),
                                  true, mojgame::X11Color::kSilver),
      MousePhisiology(*(static_cast<mojgame::PlanarEntity *>(this))),
      cheeses_(cheeses),
      waters_(waters),
      state_(kIdle),
      target_(nullptr),
      ingestingtimer_(0.0f) {
}

Mouse::~Mouse() {
}

void Mouse::Update(float elapsed_time) {
  MousePhisiology::Update(elapsed_time);

  switch (state_) {
    case kIdle: {
      if (GetAppetiteForFood() > 0.8f) {
        target_ = *(cheeses_.begin());
        state_ = kTargeting;
      } else if (GetAppetiteForDrink() > 0.8f) {
        target_ = *(waters_.begin());
        state_ = kTargeting;
      }
      break;
    }
    case kTargeting: {
      glm::vec2 totarget = target_->pos() - pos();
      Move(
          glm::normalize(totarget)
              * std::min(glm::length(totarget), 5.0f * elapsed_time));
      RotateTo(atan2(totarget.y, totarget.x) + glm::radians(90.0f));
      if (mojgame::math_aux::is_fzero(glm::length(target_->pos() - pos()))) {
        state_ = kIngesting;
        ingestingtimer_ = 1.0f;
      }
      break;
    }
    case kIngesting: {
      ingestingtimer_ = std::max(ingestingtimer_ - elapsed_time, 0.0f);
      if (mojgame::math_aux::is_fzero(ingestingtimer_)) {
        target_->Affect(*this);
        state_ = kIdle;
      }
      break;
    }
    default: {
      assert(false);
      break;
    }
  }
}
