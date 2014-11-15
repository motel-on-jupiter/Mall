/**
 * Copyright (C) 2014 The Motel on Jupiter
 */

#include "MallStage.h"
#include <boost/foreach.hpp>
#include <glm/gtx/compatibility.hpp>
#include "core/MallTweakerContext.h"
#include "util/color_sample.h"

MallStage::MallStage() : size_(), graph_() {
}

MallStage::~MallStage() {
}

int MallStage::Initialize(const glm::vec2 &size) {
  size_ = size;
  return 0;
}

void MallStage::Draw() {
  if (tweaker_ctx.stage_waypoint_visible) {
    glColor3ubv(WebColor::kWhite);
    glPointSize(3.0f);
    glBegin(GL_POINTS);
    BOOST_FOREACH(auto point, graph_.points()) {
      glVertex2fv(glm::value_ptr(point->pos()));
    }
    glEnd();
  }
  if (tweaker_ctx.stage_traceable_visible) {
    glColor3ubv(WebColor::kWhite);
    glBegin(GL_LINES);
    BOOST_FOREACH(const Waypoint *point, graph_.points()) {
      BOOST_FOREACH(const Waypoint *nextpoint, point->nextpoints()) {
        glVertex2fv(glm::value_ptr(point->pos()));
        glVertex2fv(glm::value_ptr(glm::lerp(point->pos(), nextpoint->pos(), 0.4f)));
      }
    }
    glEnd();
  }
}
