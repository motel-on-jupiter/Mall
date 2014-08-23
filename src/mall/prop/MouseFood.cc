/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "MouseFood.h"
#include "util/def/ColorDef.h"

MouseFood::MouseFood(const glm::vec2 &pos, float rot, const glm::vec2 &scale)
: BaseEntity(pos, rot, scale),
  EntityRectangleDraw(*this, true) {
}

MouseFood::~MouseFood() {
}

void MouseFood::Draw() {
  glColor3ubv(X11Color::kOrangeRed);
  EntityRectangleDraw::Draw();
}

