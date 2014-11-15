/**
 * Copyright (C) 2014 The Motel on Jupiter
 */

#ifndef MALLGAME_H_
#define MALLGAME_H_

#include <vector>

class MallBaseGameScene {
 public:
  MallBaseGameScene(const char *name)
      : name_(name) {
  }
  virtual ~MallBaseGameScene() {}

  virtual int Initialize(const glm::vec2 &stage_size) = 0;
  virtual void Finalize() = 0;
  virtual int Update(float elapsed_time) = 0;
  virtual int Draw() = 0;
  virtual int OnMouseButtonDown(unsigned char button, const glm::vec2 &cursor_pos) = 0;

  const std::string &name() const {
    return name_;
  }

 private:
  std::string name_;
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

  bool ongoing() const { return ongoing_; }

 private:
  std::vector<MallBaseGameScene *> scenes_;
  MallBaseGameScene *current_scene_;
  glm::vec2 stage_size_;
  unsigned int cursor_;
  bool ongoing_;
};

#endif /* MALLGAME_H_ */
