/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "mall/prop/AutomaticDoor.h"
#include <algorithm>
#include <boost/foreach.hpp>
#include <GL/glew.h>
#include "util/color_sample.h"
#include "util/macro_util.h"

const float AutomaticDoor::kDefaultDetectionDistance = 1.0f;
const float AutomaticDoor::kDefaultStayTime = 1.0f;
const float AutomaticDoor::kDefaultOpenSpeed = 0.04f;

AutomaticDoor::AutomaticDoor(const glm::vec2 &pos, float rot, const glm::vec2 &scale,
                             float detectdist, float staytime, float openspeed) :
BaseEntity(pos, rot, scale),
detectdist_(detectdist),
staytime_(staytime),
openspeed_(openspeed),
nodetectingtime_(FLT_MAX),
opendegree_(0.0f) {
}

AutomaticDoor::~AutomaticDoor() {
}

void AutomaticDoor::Update(float elapsedtime, const BaseEntity **detecttargets,
                           size_t numtargets) {
  bool detecting = false;
  for (unsigned int i=0; i<numtargets; ++i) {
    if (glm::length(detecttargets[i]->pos() - pos()) < detectdist_) {
      detecting = true;
      break;
    }
  }

  if (detecting) {
    nodetectingtime_ = 0.0f;
  } else {
    nodetectingtime_ += elapsedtime;
  }
  if (nodetectingtime_ < staytime_) {
    opendegree_ = std::min<float>(opendegree_ + openspeed_, 1.0f);
  } else {
    opendegree_ = std::max<float>(opendegree_ - openspeed_, 0.0f);
  }
}

void AutomaticDoor::Draw() {
  glColor3ubv(WebColor::kGray);

  glm::vec2 doorscale = scale() * 0.5f;
  glPushMatrix();
  glMultMatrixf(glm::value_ptr(glm::translate(glm::vec3(pos(), 0.0f))));

  // left door
  glPushMatrix();
  glm::vec2 leftdoorpos = glm::rotate(scale() * glm::vec2(-0.25f - 0.5f * opendegree_, 0.0f), rot());
  glMultMatrixf(glm::value_ptr(glm::translate(glm::vec3(leftdoorpos, 0.0f))));
  glBegin(GL_LINE_LOOP);
  glVertex2fv(glm::value_ptr(glm::rotate(doorscale * -0.5f, rot())));
  glVertex2fv(glm::value_ptr(glm::rotate(doorscale * glm::vec2(-0.5f, 0.5f), rot())));
  glVertex2fv(glm::value_ptr(glm::rotate(doorscale * 0.5f, rot())));
  glVertex2fv(glm::value_ptr(glm::rotate(doorscale * glm::vec2(0.5f, -0.5f), rot())));
  glEnd();
  glPopMatrix();

  // right door
  glPushMatrix();
  glm::vec2 rightdoorpos = glm::rotate(scale() * glm::vec2(0.25f + 0.5f * opendegree_, 0.0f), rot());
  glMultMatrixf(glm::value_ptr(glm::translate(glm::vec3(rightdoorpos, 0.0f))));
  glBegin(GL_LINE_LOOP);
  glVertex2fv(glm::value_ptr(glm::rotate(doorscale * -0.5f, rot())));
  glVertex2fv(glm::value_ptr(glm::rotate(doorscale * glm::vec2(-0.5f, 0.5f), rot())));
  glVertex2fv(glm::value_ptr(glm::rotate(doorscale * 0.5f, rot())));
  glVertex2fv(glm::value_ptr(glm::rotate(doorscale * glm::vec2(0.5f, -0.5f), rot())));
  glEnd();
  glPopMatrix();

  glPopMatrix();
}
