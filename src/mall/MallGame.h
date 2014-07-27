/**
 * Copyright (C) 2014 The Motel On Jupiter
 */

#ifndef MALLGAME_H_
#define MALLGAME_H_

class GLUquadric;
struct MallContext;

class MallGame {
 public:
  MallGame();
  ~MallGame();

  int Initialize();
  void Finalize();

  void Update(float elapsed_time);
  int Draw(glm::vec2 window_size);

 private:
  bool initialized_;
  glm::vec2 rect_pos_;
  glm::vec2 rect_size_;
};

#endif /* MALLGAME_H_ */
