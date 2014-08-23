/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "Mouse.h"
#include <algorithm>
#include "util/color_sample.h"
#include "mall/prop/MouseFood.h"
#include "util/math_aux.h"

Mouse::Mouse(const glm::vec2 &pos, float rot, const glm::vec2 &scale,
             std::vector<const MouseFood *> &foods)
: BaseEntity(pos, rot, scale),
  EntityTriangleDraw(*(static_cast<BaseEntity *>(this)), true, X11Color::kSilver),
  EntityPhisiology(*(static_cast<BaseEntity *>(this))),
  foods_(foods),
  target_(foods_.begin()),
  ingestingtimer_(0.0f) {
}

Mouse::~Mouse() {
}

void Mouse::Update(float elapsed_time) {
  EntityPhisiology::Update(elapsed_time);

  glm::vec2 totarget = (*target_)->pos() - pos();
  if (is_fzero(ingestingtimer_)) {
    Move(glm::normalize(totarget) * std::min(glm::length(totarget), 5.0f * elapsed_time));
    RotateTo(atan2(totarget.y, totarget.x) + glm::radians(90.0f));
    if (is_fzero(glm::length((*target_)->pos() - pos()))) {
      (*target_)->Affect(*this);
      ingestingtimer_ = 1.0f;
    }
  } else {
    ingestingtimer_ = std::max(ingestingtimer_ - elapsed_time, 0.0f);
    if (is_fzero(ingestingtimer_)) {
      // Reset the target food
      ++target_;
      if (target_ == foods_.end()) {
        target_ = foods_.begin();
      }
    }
  }
}
