/**
 * Copyright (C) 2014 The Motel On Jupiter
 */

#ifndef MALLGAME_H_
#define MALLGAME_H_

class GLUquadric;
struct MallContext;

class RectangleEntity {
 public:
  RectangleEntity(glm::vec2 pos, glm::vec2 scale);

  void Draw(glm::vec2 window_size);

 private:
  glm::vec2 pos_;
  glm::vec2 scale_;
};

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
  RectangleEntity renctangle_;
};

#endif /* MALLGAME_H_ */
