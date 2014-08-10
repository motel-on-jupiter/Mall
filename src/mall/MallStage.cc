/**
 * Copyright (C) 2014 The Motel on Jupiter
 */

#include "MallStage.h"
#include <boost/foreach.hpp>
#define GLM_COLOR
#include "util/def/ColorDef.h"

MallStage::MallStage() : size_(), graph_() {
}

MallStage::~MallStage() {
}

int MallStage::Initialize(const glm::vec2 &size) {
  size_ = size;
  return 0;
}

void MallStage::Draw() {
  glColor3fv(glm::value_ptr(kWhiteColor));
  glPointSize(0.1f);
  glBegin(GL_POINTS);
  BOOST_FOREACH(auto point, graph_.points()) {
    glVertex2f(point->pos().x / size_.x * 2.0f - 1.0f,
               point->pos().y / size_.y * 2.0f - 1.0f);
  }
  glEnd();
  glBegin(GL_LINES);
  BOOST_FOREACH(const Waypoint *point, graph_.points()) {
    BOOST_FOREACH(const Waypoint *nextpoint, point->nextpoints()) {
      glm::vec2 start = glm::vec2(point->pos().x / size_.x * 2.0f - 1.0f,
                                  point->pos().y / size_.y * 2.0f - 1.0f);
      glm::vec2 next = glm::vec2(nextpoint->pos().x / size_.x * 2.0f - 1.0f,
                                 nextpoint->pos().y / size_.y * 2.0f - 1.0f);
      glVertex2fv(glm::value_ptr(start));
      glVertex2fv(glm::value_ptr(start + (next - start) * 0.4f));
    }
  }
  glEnd();
}
