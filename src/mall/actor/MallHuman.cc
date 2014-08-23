/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "mall/actor/MallHuman.h"
#include "util/macro_util.h"

const char *MallHumanProperty::kDefaultName = "Smith";

const glm::vec2 MallHuman::kScale = glm::vec2(0.5f, 0.2f);

MallHuman::MallHuman(const glm::vec2 &pos, float rot, const GLubyte *color) :
  BaseEntity(pos, rot, kScale),
  EntityRectangleDraw(*this, true, color),
  property_() {
}

void MallHuman::Update(float elapsed_time) {
  UNUSED(elapsed_time);
}
