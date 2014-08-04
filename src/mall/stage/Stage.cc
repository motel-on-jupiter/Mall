/**
 * Copyright (C) 2014 The Motel On Jupiter
 */

#include "mall/stage/Stage.h"
#include <boost/foreach.hpp>
#define GLM_COLOR
#include "util/def/ColorDef.h"

Stage::Stage() : nodemap_() {
}

Stage::~Stage() {
}

int Stage::Initialize(const glm::vec2 &window_size) {
  return nodemap_.Initialize(window_size);
}

void Stage::Finalize() {
  nodemap_.Finalize();
}

void Stage::Draw(const glm::vec2 &window_size) {
  glColor3fv(glm::value_ptr(kWhiteColor));
  glPointSize(0.1f);
  glBegin(GL_POINTS);
  BOOST_FOREACH (auto node, nodemap_.nodes()) {
    glVertex2f(node->pos().x / window_size.x * 2.0f - 1.0f,
               node->pos().y / window_size.y * 2.0f - 1.0f);
  }
  glEnd();
}
