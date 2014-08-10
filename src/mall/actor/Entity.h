/**
 * Copyright (C) 2014 The Motel on Jupiter
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#define GLM_COLOR
#include "util/def/ColorDef.h"

class Entity {
 public:
  Entity(const glm::vec2 &pos, float rot, const glm::vec2 &scale);
  virtual ~Entity() {}

  virtual void Draw() = 0;

  glm::vec2 pos() const { return pos_; }
  void set_pos(const glm::vec2 &pos) { pos_ = pos; }
  float rot() const { return rot_; }
  void set_rot(float rot) { rot_ = rot; }
  glm::vec2 scale() const { return scale_; }
  void set_scale(const glm::vec2 &scale) { scale_ = scale; }

 private:
  glm::vec2 pos_;
  float rot_;
  glm::vec2 scale_;
};

class PointEntity : public Entity {
 public:
  PointEntity(const glm::vec2 &pos, float scale);
  virtual ~PointEntity() {}

  virtual void Draw();
};

class TriangleEntity : public Entity {
 public:
  TriangleEntity(const glm::vec2 &pos, float rot, const glm::vec2 &scale);
  virtual ~TriangleEntity() {}

  virtual void Draw();
};

class RectangleEntity : public Entity {
 public:
  RectangleEntity(const glm::vec2 &pos, float rot, const glm::vec2 &scale);
  virtual ~RectangleEntity() {}

  virtual void Draw();
};

#endif /* ENTITY_H_ */
