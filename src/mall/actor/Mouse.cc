/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "mall/actor/Mouse.h"

Mouse::Mouse(const glm::vec2 &pos, float rot, const glm::vec2 &scale)
: BaseEntity(pos, rot, scale),
  EntityTriangleDraw(*this, true) {
}

Mouse::~Mouse() {
}

