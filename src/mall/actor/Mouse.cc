/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "Mouse.h"
#include <algorithm>
#include "mall/prop/MouseFood.h"
#include "util/def/ColorDef.h"
#include "util/math_aux.h"

Mouse::Mouse(const glm::vec2 &pos, float rot, const glm::vec2 &scale,
             std::vector<const MouseFood *> &foods)
: BaseEntity(pos, rot, scale),
  EntityTriangleDraw(*(static_cast<BaseEntity *>(this)), true, X11Color::kSilver),
  EntityPhisiology(*(static_cast<BaseEntity *>(this))),
  foods_(foods),
  target_(foods_.begin()) {
}

Mouse::~Mouse() {
}

void Mouse::Update(float elapsed_time) {
  EntityPhisiology::Update(elapsed_time);

  glm::vec2 totarget = (*target_)->pos() - pos();
  if (is_fzero(glm::length(totarget))) {
    ++target_;
    if (target_ == foods_.end()) {
      target_ = foods_.begin();
    }
    totarget = (*target_)->pos() - pos();
  }
  Move(glm::normalize(totarget) * std::min(glm::length(totarget), 5.0f * elapsed_time));
  RotateTo(atan2(totarget.y, totarget.x) + glm::radians(90.0f));

}
