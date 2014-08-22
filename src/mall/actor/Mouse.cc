/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "mall/actor/Mouse.h"
#include "util/def/ColorDef.h"

Mouse::Mouse(const glm::vec2 &pos, float rot, const glm::vec2 &scale)
: BaseEntity(pos, rot, scale),
  EntityTriangleDraw(*(static_cast<BaseEntity *>(this)), true),
  EntityPhisiology(*(static_cast<BaseEntity *>(this))) {
}

Mouse::~Mouse() {
}

void Mouse::Update(float elapsed_time) {
  EntityPhisiology::Update(elapsed_time);
}

void Mouse::Draw() {
  glColor3ubv(X11Color::kSilver);
  EntityTriangleDraw::Draw();
}

