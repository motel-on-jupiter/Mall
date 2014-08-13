/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#ifndef BASEENTITY_H_
#define BASEENTITY_H_

#include <boost/noncopyable.hpp>

class BaseEntity {
 public:
  BaseEntity(const glm::vec2 &pos, float rot, const glm::vec2 &scale) :
    pos_(pos), rot_(rot), scale_(scale) {}
  virtual ~BaseEntity() {}

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

class EntityMixIn : public boost::noncopyable {
 public:
  EntityMixIn(BaseEntity &entity) : entity_(entity) {}
  virtual ~EntityMixIn() {}

 protected:
  BaseEntity &entity() { return entity_; }

 private:
  BaseEntity &entity_;
};

#endif /* BASEENTITY_H_ */
