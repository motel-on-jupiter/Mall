/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "mall/actor/GoalWalker.h"

#include <GL/glew.h>
#include <glm/gtx/random.hpp>

RectangleEntity::RectangleEntity(glm::vec2 pos, glm::vec2 scale) : pos_(pos), scale_(scale){
}

void RectangleEntity::Draw(glm::vec2 window_size) {
  glBegin(GL_QUADS);
  glVertex2f(pos_.x / window_size.x * 2.0f - 1.0f,
             pos_.y / window_size.y * 2.0f - 1.0f);
  glVertex2f(pos_.x / window_size.x * 2.0f - 1.0f,
             (pos_.y + scale_.y) / window_size.y * 2.0f - 1.0f);
  glVertex2f((pos_.x + scale_.x) / window_size.x * 2.0f - 1.0f,
             (pos_.y + scale_.y) / window_size.y * 2.0f - 1.0f);
  glVertex2f((pos_.x + scale_.x) / window_size.x * 2.0f - 1.0f,
             pos_.y / window_size.y * 2.0f - 1.0f);
  glEnd();
}

GoalWalker::GoalWalker(glm::vec2 pos) :
  RectangleEntity(pos, glm::vec2(5.0f, 5.0f)), goal_(nullptr) {
}

GoalWalker::~GoalWalker() {
  delete(goal_);
}

void GoalWalker::Update() {
  if (HasReached()) {
    return;
  }

  if (glm::distance(pos(), goal_->pos()) <= 1.0f) {
    set_pos(goal_->pos());
    free(goal_);
    goal_ = nullptr;
    return;
  }

  set_pos(pos() + glm::normalize(goal_->pos() - pos()));
}

GoalNode::GoalNode(glm::vec2 pos) : RectangleEntity(pos, glm::vec2(5.0f, 5.0f)) {
}
