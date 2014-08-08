/**
 * Copyright (C) 2014 The Motel on Jupiter
 */

#ifndef WALKER_H_
#define WALKER_H_

#include "mall/actor/Entity.h"
#include "navigation/Navigator.h"

class WalkerProperty {
 public:
  enum WalkerSex {
    kWalkerMale,
    kWalkerUndefined,
  };

  WalkerProperty() : name_(kDefaultName), sex_(kWalkerMale), age_(20), height_(180), weight_(50) {}
  ~WalkerProperty() {}

  const char* name() const { return name_; }
  void set_name(const char* name) { name_ = name; }
  WalkerSex sex() const { return sex_; }
  void set_sex(WalkerSex sex) { sex_ = sex; }
  unsigned char age() const { return age_; }
  void set_age(unsigned char age) { age_ = age; }
  unsigned char height() const { return height_; }
  void set_height(unsigned char height) { height_ = height; }
  unsigned char weight() const { return weight_; }
  void set_weight(unsigned char weight) { weight_ = weight; }

 private:
  static const char *kDefaultName;

  const char *name_;
  WalkerSex sex_;
  unsigned char age_;
  unsigned char height_;
  unsigned char weight_;
};

class Walker : public RectangleEntity {
public:
  enum WalkerStatus {
    kWalkerStandBy,
    kWalkerMoving,
    kWalkerRerouting,
  };

  Walker(const WaypointGraph &graph, const Waypoint &origin, const Waypoint &terminus);
  virtual ~Walker() {}

  void Update();
  void Reroute(const Waypoint &terminus);
  void Draw(const glm::vec2 &window_size);
  WalkerStatus CheckStatus() const;

  const WalkerProperty &property() const { return property_; }

private:
  Navigator navi_;
  const Waypoint *goal_;
  bool reached_;
  WalkerProperty property_;
};

#endif /* WALKER_H_ */
