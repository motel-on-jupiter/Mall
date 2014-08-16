/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#ifndef MALLTWEAKCONTEXT_H_
#define MALLTWEAKCONTEXT_H_

struct MallTweakContext {
  int ideal_fps;
  int actual_fps;
  bool walker_route_visible;

  MallTweakContext() : ideal_fps(0), actual_fps(0), walker_route_visible(true) {}
  ~MallTweakContext() {}
};

extern MallTweakContext tweak_ctx;

#endif /* MALLTWEAKCONTEXT_H_ */
