/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "MouseFood.h"
#include "core/actor/Mouse.h"
#include "util/color_sample.h"

MouseFood::MouseFood(const glm::vec2 &pos, float rot, const glm::vec2 &scale,
                     const GLubyte* color)
: BaseEntity(pos, rot, scale),
  EntityRectangleDraw(*this, true, color) {
}

MouseFood::~MouseFood() {
}

MouseCheese::MouseCheese(const glm::vec2& pos, float rot,
                         const glm::vec2& scale)
: MouseFood(pos, rot, scale, X11Color::kOrangeRed) {
}

MouseCheese::~MouseCheese() {
}

void MouseCheese::Affect(Mouse &mouse) const {
  mouse.GratifyAppetitleForFood(100.0f);
}

MouseWater::MouseWater(const glm::vec2& pos, float rot,
                       const glm::vec2& scale)
: MouseFood(pos, rot, scale, X11Color::kAqua) {
}

MouseWater::~MouseWater() {
}

void MouseWater::Affect(Mouse &mouse) const {
  mouse.GratifyAppetitleForDrink(100.0f);
}
