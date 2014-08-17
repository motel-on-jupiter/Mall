/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#ifndef AUTOMATICDOOR_H_
#define AUTOMATICDOOR_H_

#include <vector>
#include "entity/BaseEntity.h"

class Walker;

class AutomaticDoor : public BaseEntity {
 public:
  static const float kDefaultDetectionDistance;
  static const float kDefaultStayTime;
  static const float kDefaultOpenSpeed;

  AutomaticDoor(const glm::vec2 &pos, float rot,
                float detectdist = kDefaultDetectionDistance,
                float staytime = kDefaultStayTime,
                float openspeed = kDefaultOpenSpeed);
  virtual ~AutomaticDoor();

  void Update(float elapsedtime, const BaseEntity **detecttargets,
              size_t numtargets);
  void Draw();

  float detectdist() const { return detectdist_; }
  float opendegree() const { return opendegree_; }
  float openspeed() const { return openspeed_; }
  float staytime() const { return staytime_; }

 private:
  float detectdist_;
  float staytime_;
  float openspeed_;
  float nodetectingtime_;
  float opendegree_;
};

#endif /* AUTOMATICDOOR_H_ */
