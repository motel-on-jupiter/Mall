/**
 * Copyright (C) 2014 The Motel On Jupiter
 */

#ifndef ENTITY_H_
#define ENTITY_H_

class Entity {
 public:
  Entity(const glm::vec2 &pos, const glm::vec2 &scale);
  virtual ~Entity() {}

  virtual void Draw(const glm::vec2 &window_size) = 0;

  glm::vec2 pos() const { return pos_; }
  void set_pos(const glm::vec2 &pos) { pos_ = pos; }
  glm::vec2 scale() const { return scale_; }
  void set_scale(const glm::vec2 &scale) { scale_ = scale; }

 private:
  glm::vec2 pos_;
  glm::vec2 scale_;
};

class PointEntity : public Entity {
 public:
  PointEntity(const glm::vec2 &pos);
  virtual ~PointEntity() {}

  virtual void Draw(const glm::vec2 &window_size);
};

class RectangleEntity : public Entity {
 public:
  RectangleEntity(const glm::vec2 &pos, const glm::vec2 &scale);
  virtual ~RectangleEntity() {}

  virtual void Draw(const glm::vec2 &window_size);
};

#endif /* ENTITY_H_ */