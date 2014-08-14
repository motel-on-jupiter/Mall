/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#ifndef MALLTWEAKCONTEXT_H_
#define MALLTWEAKCONTEXT_H_

struct MallTweakContext {
  bool walker_route_visible;

  MallTweakContext() : walker_route_visible(true) {}
  ~MallTweakContext() {}
};

extern MallTweakContext tweak_ctx;

#endif /* MALLTWEAKCONTEXT_H_ */
