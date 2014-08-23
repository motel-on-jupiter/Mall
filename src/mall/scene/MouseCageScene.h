/**
 * Copyright (C) 2014 The Motel on Jupiter
 */

#ifndef MOUSECAGESCENE_H_
#define MOUSECAGESCENE_H_

#include "mall/MallGame.h"
#include "mall/MallStage.h"

class Mouse;
class MouseFood;

class MouseCageStage : public MallStage {
 public:
  MouseCageStage();
  virtual ~MouseCageStage();

  virtual int Initialize(const glm::vec2 &size);
  virtual void Finalize();
};

class MouseCageScene : public MallGameSceneInterface {
 public:
  MouseCageScene();
  virtual ~MouseCageScene();

  virtual int Initialize(const glm::vec2 &stage_size);
  virtual void Finalize();
  virtual int Update(float elapsed_time);
  virtual int Draw();
  virtual int OnMouseButtonDown(unsigned char button, const glm::vec2 &cursor_pos);

 private:
  MouseCageStage stage_;
  Mouse *mouse_;
  MouseFood *food_;
};

#endif /* MOUSECAGESCENE_H_ */
