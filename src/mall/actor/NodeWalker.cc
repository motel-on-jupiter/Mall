/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "mall/actor/NodeWalker.h"

#include <GL/glew.h>

#include "util/logging/Logger.h"
#include "util/macro_util.h"
#define GLM_COLOR
#include "util/def/ColorDef.h"

NodeWalker::NodeWalker(const WalkNode &start) :
  RectangleEntity(start.pos(), glm::vec2(5.0f, 5.0f)), goal_(nullptr), arrived_(true) {
}

void NodeWalker::Update() {
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

void NodeWalker::DrawApproach(const glm::vec2 &window_size) {
  if (goal_ != nullptr) {
    glColor3fv(glm::value_ptr(kYellowColor));
    glBegin(GL_LINE_LOOP);
    glVertex2f(pos().x / window_size.x * 2.0f - 1.0f, pos().y / window_size.y * 2.0f - 1.0f);
    glVertex2f(goal_->pos().x / window_size.x * 2.0f - 1.0f, goal_->pos().y / window_size.y * 2.0f - 1.0f);
    glEnd();
  }
}

void NodeWalker::SelectNextGoal(const WalkNode *current_goal) {
  UNUSED(current_goal);
}

NodeMapWalker::NodeMapWalker(const WalkNode &start, const WalkNodeMap &nodemap) :
  NodeWalker(start), nodemap_(nodemap), travelnodelist_(nullptr), finalgoal_(nullptr) {
  SetGoal(&start);
}

NodeMapWalker::~NodeMapWalker() {
  delete travelnodelist_;
}

int NodeMapWalker::BuildTravelNodeList(const WalkNode *finalgoal) {
  std::vector<const WalkNode *> listbuf;
  std::vector<const WalkNode *> *minlist = nullptr;
  if (BuildTravelNodeListImpl(goal(), finalgoal, listbuf, &minlist) < 0) {
    LOGGER.Error("Failed to deep-copy braedcrumbs as the minimun length node list");
    delete minlist;
    return -1;
  }
  delete travelnodelist_;
  travelnodelist_ = minlist;
  return 0;
}

int NodeMapWalker::UpdateFinalGoal(const WalkNode *finalgoal) {
  if ((finalgoal != nullptr) && (goal() != nullptr)) {
    if (BuildTravelNodeList(finalgoal) < 0) {
      LOGGER.Error("Failed to build the travel node list");
      return -1;
    }
  }
  finalgoal_ = finalgoal;
  return 0;
}

void NodeMapWalker::DrawApproach(const glm::vec2 &window_size) {
  NodeWalker::DrawApproach(window_size);
  if (finalgoal_ != nullptr) {
    glColor3fv(glm::value_ptr(kRedColor));
    glBegin(GL_LINE_LOOP);
    glVertex2f(pos().x / window_size.x * 2.0f - 1.0f, pos().y / window_size.y * 2.0f - 1.0f);
    glVertex2f(finalgoal_->pos().x / window_size.x * 2.0f - 1.0f, finalgoal_->pos().y / window_size.y * 2.0f - 1.0f);
    glEnd();
  }
}

void NodeMapWalker::SelectNextGoal(const WalkNode *current_goal) {
  UNUSED(current_goal);

  if ((travelnodelist_ != NULL) && (travelnodelist_->size() != 0)) {
    SetGoal(travelnodelist_->front());
    travelnodelist_->erase(travelnodelist_->begin());
  }
}

RandomNodeMapWalker::RandomNodeMapWalker(const WalkNode &start, const WalkNodeMap &nodemap) :
  NodeWalker(start), nodemap_(nodemap) {

}

void RandomNodeMapWalker::SelectNextGoal(const WalkNode *current_goal) {
  if (current_goal != nullptr) {
    int nodeidx = static_cast<int>(glm::linearRand(0.0f, static_cast<float>(current_goal->nextnodes().size())));
    SetGoal(current_goal->nextnodes()[nodeidx]);
  }
}
