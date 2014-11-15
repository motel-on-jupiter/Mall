/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#ifndef MALLTWEAKERCONTEXT_H_
#define MALLTWEAKERCONTEXT_H_

struct MallTweakerContext {
  int system_actual_fps;
  float system_time_speed;
  bool walker_route_visible;
  bool stage_waypoint_visible;
  bool stage_traceable_visible;

  MallTweakerContext();
  ~MallTweakerContext();
};

extern MallTweakerContext tweaker_ctx;

#endif /* MALLTWEAKERCONTEXT_H_ */
