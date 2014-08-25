/**
 * Copyright (C) 2014 The Motel on Jupiter
 */

#ifndef MALLGAME_H_
#define MALLGAME_H_

#include <vector>
#include <SDL_ttf.h>

class MallGameSceneInterface {
 public:
  MallGameSceneInterface() {}
  virtual ~MallGameSceneInterface() {}

  virtual int Initialize(const glm::vec2 &stage_size) = 0;
  virtual void Finalize() = 0;
  virtual int Update(float elapsed_time) = 0;
  virtual int Draw() = 0;
  virtual int OnMouseButtonDown(unsigned char button, const glm::vec2 &cursor_pos) = 0;
};

class MallGame {
 public:
  MallGame();
  ~MallGame();

  int Initialize(const glm::vec2 &stage_size);
  void Finalize();
  int Update(float elapsed_time);
  int Draw(const glm::vec2 &window_size);
  int OnKeyboardDown(SDL_Keycode key);
  int OnMouseButtonDown(unsigned char button, int x, int y, const glm::vec2 &window_size);

 private:
  std::vector<MallGameSceneInterface *> scenes_;
  MallGameSceneInterface *activescene_;
  glm::vec2 stagesize_;
  TTF_Font *font_;
};

#endif /* MALLGAME_H_ */
