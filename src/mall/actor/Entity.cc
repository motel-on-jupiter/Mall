/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "mall/actor/Entity.h"
#include <GL/glew.h>
#include <glm/gtx/rotate_vector.hpp>

Entity::Entity(const glm::vec2 &pos, float rot, const glm::vec2 &scale) :
  pos_(pos), rot_(rot), scale_(scale){
}

PointEntity::PointEntity(const glm::vec2 &pos, float scale) :
  Entity(pos, 0.0f, glm::vec2(scale)) {
}

void PointEntity::Draw() {
  glPointSize(scale().x);
  glBegin(GL_POINTS);
  glVertex2fv(glm::value_ptr(pos()));
  glEnd();
}

TriangleEntity::TriangleEntity(const glm::vec2 &pos, float rot, const glm::vec2 &scale) :
  Entity(pos, rot, scale) {
}

void TriangleEntity::Draw() {
  glBegin(GL_LINE_LOOP);
  glVertex2fv(glm::value_ptr(pos() + glm::rotate(scale() * glm::vec2(0.0f, -0.5f), rot())));
  glVertex2fv(glm::value_ptr(pos() + glm::rotate(glm::vec2(scale() * glm::vec2(-0.5f, 0.5f)), rot())));
  glVertex2fv(glm::value_ptr(pos() + glm::rotate(glm::vec2(scale() * glm::vec2(0.5f, 0.5f)), rot())));
  glEnd();
}

RectangleEntity::RectangleEntity(const glm::vec2 &pos, float rot, const glm::vec2 &scale) :
  Entity(pos, rot, scale) {
}

void RectangleEntity::Draw() {
  glBegin(GL_LINE_LOOP);
  glVertex2fv(glm::value_ptr(pos() + glm::rotate(scale() * -0.5f, rot())));
  glVertex2fv(glm::value_ptr(pos() + glm::rotate(scale() * glm::vec2(-0.5f, 0.5f), rot())));
  glVertex2fv(glm::value_ptr(pos() + glm::rotate(scale() * 0.5f, rot())));
  glVertex2fv(glm::value_ptr(pos() + glm::rotate(scale() * glm::vec2(0.5f, -0.5f), rot())));
  glEnd();
}
