/**
 * Copyright (C) 2014 The Motel On Jupiter
 */

#ifndef MALLGAME_H_
#define MALLGAME_H_

#include "mall/actor/Walker.h"
#include "mall/stage/Stage.h"

class MallGameCaseInterface {
 public:
  MallGameCaseInterface() {}
  virtual ~MallGameCaseInterface() {}

  virtual int Initialize(const glm::vec2 &window_size) = 0;
  virtual void Finalize() = 0;
  virtual void Update(float elapsed_time) = 0;
  virtual int Draw(glm::vec2 window_size) = 0;
  virtual int OnMouseButtonDown(unsigned char button, int x, int y, glm::vec2 window_size) = 0;
};

class GridWalkingCase : public MallGameCaseInterface {
 public:
  GridWalkingCase();
  ~GridWalkingCase();

  int Initialize(const glm::vec2 &window_size);
  void Finalize();
  void Update(float elapsed_time);
  int Draw(glm::vec2 window_size);
  int OnMouseButtonDown(unsigned char button, int x, int y, glm::vec2 window_size);

 private:
  static const int kNumWalkWalkers;

  bool initialized_;
  RoughGridStage stage_;
  std::vector<Walker *> walkers_;
};

class MallGame {
 public:
  MallGame();
  ~MallGame();

  void Initialize();
  void Finalize();
  void Update(float elapsed_time);
  int Draw(glm::vec2 window_size);
  int OnKeyboardDown(SDL_Keycode key, glm::vec2 window_size);
  int OnMouseButtonDown(unsigned char button, int x, int y, glm::vec2 window_size);

 private:
  MallGameCaseInterface *gamecase_;
};

#endif /* MALLGAME_H_ */
