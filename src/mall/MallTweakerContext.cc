/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "mall/MallTweakerContext.h"

MallTweakerContext::MallTweakerContext()
: ideal_fps(0),
  actual_fps(0),
  walker_route_visible(false) {
}

MallTweakerContext::~MallTweakerContext() {
}

MallTweakerContext tweaker_ctx;
