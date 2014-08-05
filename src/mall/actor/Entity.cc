/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "mall/actor/Entity.h"
#include <GL/glew.h>

Entity::Entity(const glm::vec2 &pos, const glm::vec2 &scale) :
  pos_(pos), scale_(scale){
}

PointEntity::PointEntity(const glm::vec2 &pos) :
    Entity(pos, glm::vec2()) {
}

void PointEntity::Draw(const glm::vec2 &window_size, const glm::vec3 &color) {
  glColor3fv(glm::value_ptr(color));
  glPointSize(0.1f);
  glBegin(GL_POINTS);
  glVertex2f(pos().x / window_size.x * 2.0f - 1.0f,
             pos().y / window_size.y * 2.0f - 1.0f);
  glEnd();
}

RectangleEntity::RectangleEntity(const glm::vec2 &pos, const glm::vec2 &scale) :
  Entity(pos, scale) {
}

void RectangleEntity::Draw(const glm::vec2 &window_size, const glm::vec3 &color) {
  glColor3fv(glm::value_ptr(color));
  glBegin(GL_QUADS);
  glVertex2f((pos().x - scale().x / 2.0f) / window_size.x * 2.0f - 1.0f,
             (pos().y - scale().y / 2.0f) / window_size.y * 2.0f - 1.0f);
  glVertex2f((pos().x - scale().x / 2.0f) / window_size.x * 2.0f - 1.0f,
             (pos().y + scale().y / 2.0f) / window_size.y * 2.0f - 1.0f);
  glVertex2f((pos().x + scale().x / 2.0f) / window_size.x * 2.0f - 1.0f,
             (pos().y + scale().y / 2.0f) / window_size.y * 2.0f - 1.0f);
  glVertex2f((pos().x + scale().x / 2.0f) / window_size.x * 2.0f - 1.0f,
             (pos().y - scale().y / 2.0f) / window_size.y * 2.0f - 1.0f);
  glEnd();
}
