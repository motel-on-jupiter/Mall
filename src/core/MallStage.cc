/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "core/MallStage.h"
#include "core/MallTweakerContext.h"
#include "mojgame/includer/glm_include.h"
#include "mojgame/sampler/color_sample.h"

MallStage::MallStage()
    : size_(),
      graph_() {
}

MallStage::~MallStage() {
}

int MallStage::Initialize(const glm::vec2 &size) {
  size_ = size;
  return 0;
}

void MallStage::Draw() {
  if (tweaker_ctx.stage_waypoint_visible) {
    glColor3ubv(mojgame::WebColor::kWhite);
    glPointSize(3.0f);
    glBegin (GL_POINTS);
    for (auto it = graph_.points().begin(); it != graph_.points().end(); ++it) {
      glVertex2fv(glm::value_ptr((*it)->pos()));
    }
    glEnd();
  }
  if (tweaker_ctx.stage_traceable_visible) {
    glColor3ubv(mojgame::WebColor::kWhite);
    glBegin (GL_LINES);
    for (auto points_it = graph_.points().begin();
        points_it != graph_.points().end(); ++points_it) {
      mojgame::Waypoint *point = *points_it;
      for (auto it = point->nextpoints().begin();
          it != point->nextpoints().end(); ++it) {
        glVertex2fv(glm::value_ptr(point->pos()));
        glVertex2fv(
            glm::value_ptr(glm::lerp(point->pos(), (*it)->pos(), 0.4f)));
      }
    }
    glEnd();
  }
}
