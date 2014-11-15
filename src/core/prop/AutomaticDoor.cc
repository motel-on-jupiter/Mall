/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "core/prop/AutomaticDoor.h"
#include <algorithm>
#include "mojgame/auxiliary/csyntax_aux.h"
#include "mojgame/includer/gl_include.h"
#include "mojgame/sampler/color_sample.h"

const float AutomaticDoor::kDefaultDetectionDistance = 1.0f;
const float AutomaticDoor::kDefaultStayTime = 1.0f;
const float AutomaticDoor::kDefaultOpenSpeed = 0.04f;

AutomaticDoor::AutomaticDoor(const glm::vec2 &pos, float rot,
                             const glm::vec2 &scale, float detectdist,
                             float staytime, float openspeed)
    : mojgame::PlanarEntity(pos, rot, scale),
      detectdist_(detectdist),
      staytime_(staytime),
      openspeed_(openspeed),
      nodetectingtime_(FLT_MAX),
      opendegree_(0.0f) {
}

AutomaticDoor::~AutomaticDoor() {
}

void AutomaticDoor::Update(float elapsedtime,
                           const mojgame::PlanarEntity **detecttargets,
                           size_t numtargets) {
  bool detecting = false;
  for (unsigned int i = 0; i < numtargets; ++i) {
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
  glColor3ubv(mojgame::WebColor::kGray);

  glm::vec2 doorscale = size() * 0.5f;
  glPushMatrix();
  glMultMatrixf(glm::value_ptr(glm::translate(glm::vec3(pos(), 0.0f))));

  // left door
  glPushMatrix();
  glm::vec2 leftdoorpos = glm::rotate(
      size() * glm::vec2(-0.25f - 0.5f * opendegree_, 0.0f), rot());
  glMultMatrixf(glm::value_ptr(glm::translate(glm::vec3(leftdoorpos, 0.0f))));
  glBegin(GL_LINE_LOOP);
  glVertex2fv(glm::value_ptr(glm::rotate(doorscale * -0.5f, rot())));
  glVertex2fv(
      glm::value_ptr(glm::rotate(doorscale * glm::vec2(-0.5f, 0.5f), rot())));
  glVertex2fv(glm::value_ptr(glm::rotate(doorscale * 0.5f, rot())));
  glVertex2fv(
      glm::value_ptr(glm::rotate(doorscale * glm::vec2(0.5f, -0.5f), rot())));
  glEnd();
  glPopMatrix();

  // right door
  glPushMatrix();
  glm::vec2 rightdoorpos = glm::rotate(
      size() * glm::vec2(0.25f + 0.5f * opendegree_, 0.0f), rot());
  glMultMatrixf(glm::value_ptr(glm::translate(glm::vec3(rightdoorpos, 0.0f))));
  glBegin(GL_LINE_LOOP);
  glVertex2fv(glm::value_ptr(glm::rotate(doorscale * -0.5f, rot())));
  glVertex2fv(
      glm::value_ptr(glm::rotate(doorscale * glm::vec2(-0.5f, 0.5f), rot())));
  glVertex2fv(glm::value_ptr(glm::rotate(doorscale * 0.5f, rot())));
  glVertex2fv(
      glm::value_ptr(glm::rotate(doorscale * glm::vec2(0.5f, -0.5f), rot())));
  glEnd();
  glPopMatrix();

  glPopMatrix();
}
