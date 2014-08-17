/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#ifndef MALLTWEAKERCONTEXT_H_
#define MALLTWEAKERCONTEXT_H_

struct MallTweakerContext {
  int system_ideal_fps;
  int system_actual_fps;
  bool walker_route_visible;

  MallTweakerContext();
  ~MallTweakerContext();
};

extern MallTweakerContext tweaker_ctx;

#endif /* MALLTWEAKERCONTEXT_H_ */
