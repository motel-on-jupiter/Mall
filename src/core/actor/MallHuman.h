/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#ifndef CORE_ACTOR_MALLHUMAN_H_
#define CORE_ACTOR_MALLHUMAN_H_

#include "mojgame/catalogue/entity_extention/PlanarEntityDraw.h"
#include "mojgame/entity/PlanarEntity.h"

class MallHumanProperty {
 public:
  enum MallHumanSex {
    kSexMale,
    kSexFemale,
  };

  MallHumanProperty() : name_(kDefaultName), sex_(kSexMale), age_(20), height_(180), weight_(50) {}
  ~MallHumanProperty() {}

  const char *name() const { return name_; }
  void set_name(const char *name) { name_ = name; }
  MallHumanSex sex() const { return sex_; }
  void set_sex(MallHumanSex sex) { sex_ = sex; }
  unsigned char age() const { return age_; }
  void set_age(unsigned char age) { age_ = age; }
  unsigned char height() const { return height_; }
  void set_height(unsigned char height) { height_ = height; }
  unsigned char weight() const { return weight_; }
  void set_weight(unsigned char weight) { weight_ = weight; }

 private:
  static const char *kDefaultName;

  const char *name_;
  MallHumanSex sex_;
  unsigned char age_;
  unsigned char height_;
  unsigned char weight_;
};

class MallHuman : public mojgame::PlanarEntity, public mojgame::EntityRectangleDraw {
public:
  static const glm::vec2 kScale;

  MallHuman(const glm::vec2 &pos, float rot, const GLubyte *color);
  virtual ~MallHuman() {}

  const MallHumanProperty &property() const { return property_; }

private:
  MallHumanProperty property_;
};

#endif /* CORE_ACTOR_MALLHUMAN_H_ */