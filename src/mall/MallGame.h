/**
 * Copyright (C) 2014 The Motel on Jupiter
 */

#ifndef MALLGAME_H_
#define MALLGAME_H_

class MallGameSceneInterface {
 public:
  MallGameSceneInterface() {}
  virtual ~MallGameSceneInterface() {}

  virtual int Initialize(const glm::vec2 &stage_size) = 0;
  virtual void Finalize() = 0;
  virtual void Update(float elapsed_time) = 0;
  virtual int Draw(glm::vec2 window_size) = 0;
  virtual int OnMouseButtonDown(unsigned char button, int x, int y, glm::vec2 window_size) = 0;
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
  MallGameSceneInterface *gamecase_;
};

#endif /* MALLGAME_H_ */
