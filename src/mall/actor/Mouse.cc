/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "Mouse.h"
#include <algorithm>
#include "util/color_sample.h"
#include "mall/prop/MouseFood.h"
#include "util/math_aux.h"

Mouse::Mouse(const glm::vec2 &pos, float rot, const glm::vec2 &scale,
             const std::vector<const MouseCheese *> &cheeses,
             const std::vector<const MouseWater *> &waters)
: BaseEntity(pos, rot, scale),
  EntityTriangleDraw(*(static_cast<BaseEntity *>(this)), true, X11Color::kSilver),
  EntityPhisiology(*(static_cast<BaseEntity *>(this))),
  cheeses_(cheeses),
  waters_(waters),
  state_(kIdle),
  target_(nullptr),
  ingestingtimer_(0.0f) {
}

Mouse::~Mouse() {
}

void Mouse::Update(float elapsed_time) {
  EntityPhisiology::Update(elapsed_time);

  switch(state_) {
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
      Move(glm::normalize(totarget) * std::min(glm::length(totarget), 5.0f * elapsed_time));
      RotateTo(atan2(totarget.y, totarget.x) + glm::radians(90.0f));
      if (is_fzero(glm::length(target_->pos() - pos()))) {
        state_ = kIngesting;
        ingestingtimer_ = 1.0f;
      }
      break;
    }
    case kIngesting: {
      ingestingtimer_ = std::max(ingestingtimer_ - elapsed_time, 0.0f);
      if (is_fzero(ingestingtimer_)) {
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
