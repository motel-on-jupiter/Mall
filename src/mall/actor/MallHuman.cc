/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "mall/actor/MallHuman.h"
#include "util/macro_util.h"

const char *MallHumanProperty::kDefaultName = "Smith";

MallHuman::MallHuman(const glm::vec2 &pos, float rot) :
  RectangleEntity(pos, rot, glm::vec2(0.5f, 0.2f), true),
  property_() {
}

void MallHuman::Update(float elapsed_time) {
  UNUSED(elapsed_time);
}
