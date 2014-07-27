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

  int Initialize(int window_width, int window_height);
  void Finalize();

  void Update(float elapsed_time);
  int Draw();

 private:
  bool initialized_;
  GLUquadric *quadric_;
};

#endif /* MALLGAME_H_ */
