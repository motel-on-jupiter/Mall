/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "mall/actor/Walker.h"

#include <GL/glew.h>

#define GLM_COLOR
#include "util/def/ColorDef.h"

GoalWalker::GoalWalker(const glm::vec2 &pos) :
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
    goal_ = nullptr;
    return;
  }

  set_pos(pos() + glm::normalize(goal_->pos() - pos()));
}

#ifdef _DEBUG
void GoalWalker::DebugDraw(const glm::vec2 &window_size) {
  if (goal_ != nullptr) {
    glColor3fv(glm::value_ptr(kYellowColor));
    glBegin(GL_LINE_LOOP);
    glVertex2f(pos().x / window_size.x * 2.0f - 1.0f, pos().y / window_size.y * 2.0f - 1.0f);
    glVertex2f(goal_->pos().x / window_size.x * 2.0f - 1.0f, goal_->pos().y / window_size.y * 2.0f - 1.0f);
    glEnd();
  }
}
#endif // _DEBUG

NodeWalker::NodeWalker(const WalkNode &node) : GoalWalker(node.pos()) {
}
