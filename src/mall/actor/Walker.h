/**
 * Copyright (C) 2014 The Motel on Jupiter
 */

#ifndef WALKER_H_
#define WALKER_H_

#include "mall/actor/Entity.h"
#include "navigation/Navigator.h"

class MallHumanProperty {
 public:
  enum MallHumanSex {
    kSexMale,
    kSexFemale,
  };

  MallHumanProperty() : name_(kDefaultName), sex_(kSexMale), age_(20), height_(180), weight_(50) {}
  ~MallHumanProperty() {}

  const char* name() const { return name_; }
  void set_name(const char* name) { name_ = name; }
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

class MallHuman : public RectangleEntity {
public:
  MallHuman(const glm::vec2 &pos, float rot);
  virtual ~MallHuman() {}

  virtual void Update(float elapsed_time);

  const MallHumanProperty &property() const { return property_; }

private:
  MallHumanProperty property_;
};

class Walker : public MallHuman {
public:
  enum WalkerStatus {
    kWalkerStandBy,
    kWalkerMoving,
    kWalkerRerouting,
  };

  Walker(const WaypointGraph &graph, const Waypoint &origin, const Waypoint &terminus);
  virtual ~Walker() {}

  virtual void Update(float elapsed_time);
  void Reroute(const Waypoint &terminus);
  virtual void Draw();
  WalkerStatus CheckStatus() const;

  Navigator &navi() { return navi_; }

private:
  Navigator navi_;
  const Waypoint *goal_;
  bool reached_;
  float speed_;
};

#endif /* WALKER_H_ */
