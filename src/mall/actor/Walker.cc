/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "mall/actor/Walker.h"

#include <GL/glew.h>

#include "util/logging/Logger.h"
#include "util/macro_util.h"
#define GLM_COLOR
#include "util/def/ColorDef.h"

SimpleWalker::SimpleWalker(const Waypoint &start) :
  RectangleEntity(start.pos(), glm::vec2(5.0f, 5.0f)), goal_(nullptr), arrived_(true) {
}

void SimpleWalker::Update() {
  if (arrived_) {
    SelectNextGoal(goal_);
    return;
  }

  if (goal_ == nullptr) {
    return;
  }
  if (glm::distance(pos(), goal_->pos()) <= 1.0f) {
    set_pos(goal_->pos());
    arrived_ = true;
  } else {
    set_pos(pos() + glm::normalize(goal_->pos() - pos()));
  }
}

void SimpleWalker::DrawApproach(const glm::vec2 &window_size) {
  if (goal_ != nullptr) {
    glColor3fv(glm::value_ptr(kYellowColor));
    glBegin(GL_LINE_LOOP);
    glVertex2f(pos().x / window_size.x * 2.0f - 1.0f, pos().y / window_size.y * 2.0f - 1.0f);
    glVertex2f(goal_->pos().x / window_size.x * 2.0f - 1.0f, goal_->pos().y / window_size.y * 2.0f - 1.0f);
    glEnd();
  }
}

void SimpleWalker::SelectNextGoal(const Waypoint *current_goal) {
  UNUSED(current_goal);
}

Walker::Walker(const Waypoint &start, const WaypointGraph &graph) :
  SimpleWalker(start), graph_(graph), travellist_(nullptr), finalgoal_(nullptr) {
  SetGoal(&start);
}

Walker::~Walker() {
  delete travellist_;
}

int Walker::BuildTravelList(const Waypoint *finalgoal) {
  std::vector<const Waypoint *> listbuf;
  std::vector<const Waypoint *> *minlist = nullptr;
  if (BuildTravelListImpl(goal(), finalgoal, listbuf, &minlist) < 0) {
    LOGGER.Error("Failed to deep-copy braedcrumbs as the minimun length list");
    delete minlist;
    return -1;
  }
  delete travellist_;
  travellist_ = minlist;
  return 0;
}

int Walker::UpdateFinalGoal(const Waypoint *finalgoal) {
  if ((finalgoal != nullptr) && (goal() != nullptr)) {
    if (BuildTravelList(finalgoal) < 0) {
      LOGGER.Error("Failed to build the travel list");
      return -1;
    }
  }
  finalgoal_ = finalgoal;
  return 0;
}

void Walker::DrawApproach(const glm::vec2 &window_size) {
  SimpleWalker::DrawApproach(window_size);
  if (finalgoal_ != nullptr) {
    glColor3fv(glm::value_ptr(kRedColor));
    glBegin(GL_LINE_LOOP);
    glVertex2f(pos().x / window_size.x * 2.0f - 1.0f, pos().y / window_size.y * 2.0f - 1.0f);
    glVertex2f(finalgoal_->pos().x / window_size.x * 2.0f - 1.0f, finalgoal_->pos().y / window_size.y * 2.0f - 1.0f);
    glEnd();
  }
}

void Walker::SelectNextGoal(const Waypoint *current_goal) {
  UNUSED(current_goal);

  if ((travellist_ != NULL) && (travellist_->size() != 0)) {
    SetGoal(travellist_->front());
    travellist_->erase(travellist_->begin());
  }
}

RandomWalker::RandomWalker(const Waypoint &start, const WaypointGraph &graph) :
  SimpleWalker(start), graph_(graph) {

}

void RandomWalker::SelectNextGoal(const Waypoint *current_goal) {
  if (current_goal != nullptr) {
    int idx = static_cast<int>(glm::linearRand(0.0f, static_cast<float>(current_goal->nextpoints().size())));
    SetGoal(current_goal->nextpoints()[idx]);
  }
}
