/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "entity/EntityDraw.h"
#include <GL/glew.h>
#include <glm/gtx/rotate_vector.hpp>
#include "entity/BaseEntity.h"

EntityPointDraw::EntityPointDraw(BaseEntity &entity) :
  EntityDraw(entity) {
}

void EntityPointDraw::Draw() {
  glPointSize(entity().scale().x);
  glBegin(GL_POINTS);
  glVertex2fv(glm::value_ptr(entity().pos()));
  glEnd();
}

EntityTriangleDraw::EntityTriangleDraw(BaseEntity &entity, bool fill) :
  EntityDraw(entity), fill_(fill) {
}

void EntityTriangleDraw::Draw() {
  glBegin(fill_ ? GL_TRIANGLES : GL_LINE_LOOP);
  glVertex2fv(glm::value_ptr(entity().pos() + glm::rotate(entity().scale() * glm::vec2(0.0f, -0.5f), entity().rot())));
  glVertex2fv(glm::value_ptr(entity().pos() + glm::rotate(glm::vec2(entity().scale() * glm::vec2(-0.5f, 0.5f)), entity().rot())));
  glVertex2fv(glm::value_ptr(entity().pos() + glm::rotate(glm::vec2(entity().scale() * glm::vec2(0.5f, 0.5f)), entity().rot())));
  glEnd();
}

EntityRectangleDraw::EntityRectangleDraw(BaseEntity &entity, bool fill) :
  EntityDraw(entity), fill_(fill) {
}

void EntityRectangleDraw::Draw() {
  glBegin(fill_ ? GL_QUADS : GL_LINE_LOOP);
  glVertex2fv(glm::value_ptr(entity().pos() + glm::rotate(entity().scale() * -0.5f, entity().rot())));
  glVertex2fv(glm::value_ptr(entity().pos() + glm::rotate(entity().scale() * glm::vec2(-0.5f, 0.5f), entity().rot())));
  glVertex2fv(glm::value_ptr(entity().pos() + glm::rotate(entity().scale() * 0.5f, entity().rot())));
  glVertex2fv(glm::value_ptr(entity().pos() + glm::rotate(entity().scale() * glm::vec2(0.5f, -0.5f), entity().rot())));
  glEnd();
}
