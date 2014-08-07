/**
 * Copyright (C) 2014 The Motel On Jupiter
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

void PointEntity::Draw(const glm::vec2 &window_size, const glm::vec3 &color) {
  glColor3fv(glm::value_ptr(color));
  glPointSize(scale().x);
  glBegin(GL_POINTS);
  glVertex2f(pos().x / window_size.x * 2.0f - 1.0f,
             pos().y / window_size.y * 2.0f - 1.0f);
  glEnd();
}

TriangleEntity::TriangleEntity(const glm::vec2 &pos, float rot, const glm::vec2 &scale) :
  Entity(pos, rot, scale) {
}

void TriangleEntity::Draw(const glm::vec2 &window_size, const glm::vec3 &color) {
  glColor3fv(glm::value_ptr(color));
  glBegin(GL_LINE_LOOP);
  glm::vec2 offset = glm::rotate(scale() * glm::vec2(0.0f, -0.5f), rot());
  glVertex2fv(glm::value_ptr((pos() + offset) / window_size * 2.0f - 1.0f));
  offset = glm::rotate(glm::vec2(scale() * glm::vec2(-0.5f, 0.5f)), rot());
  glVertex2fv(glm::value_ptr((pos() + offset) / window_size * 2.0f - 1.0f));
  offset = glm::rotate(glm::vec2(scale() * glm::vec2(0.5f, 0.5f)), rot());
  glVertex2fv(glm::value_ptr((pos() + offset) / window_size * 2.0f - 1.0f));
  glEnd();
}

RectangleEntity::RectangleEntity(const glm::vec2 &pos, float rot, const glm::vec2 &scale) :
  Entity(pos, rot, scale) {
}

void RectangleEntity::Draw(const glm::vec2 &window_size, const glm::vec3 &color) {
  glColor3fv(glm::value_ptr(color));
  glBegin(GL_LINE_LOOP);
  glm::vec2 offset = glm::rotate(scale() * -0.5f, rot());
  glVertex2fv(glm::value_ptr((pos() + offset) / window_size * 2.0f - 1.0f));
  offset = glm::rotate(scale() * glm::vec2(-0.5f, 0.5f), rot());
  glVertex2fv(glm::value_ptr((pos() + offset) / window_size * 2.0f - 1.0f));
  offset = glm::rotate(scale() * 0.5f, rot());
  glVertex2fv(glm::value_ptr((pos() + offset) / window_size * 2.0f - 1.0f));
  offset = glm::rotate(scale() * glm::vec2(0.5f, -0.5f), rot());
  glVertex2fv(glm::value_ptr((pos() + offset) / window_size * 2.0f - 1.0f));
  glEnd();
}
