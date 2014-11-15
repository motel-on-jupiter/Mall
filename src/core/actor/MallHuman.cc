/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "core/actor/MallHuman.h"

const char *MallHumanProperty::kDefaultName = "Smith";

const glm::vec2 MallHuman::kScale = glm::vec2(0.5f, 0.2f);

MallHuman::MallHuman(const glm::vec2 &pos, float rot, const GLubyte *color) :
  mojgame::PlanarEntity(pos, rot, kScale),
  mojgame::EntityRectangleDraw(*this, true, color),
  property_() {
}
