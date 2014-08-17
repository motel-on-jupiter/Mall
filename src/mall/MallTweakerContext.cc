/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "mall/MallTweakerContext.h"

MallTweakerContext::MallTweakerContext()
: system_actual_fps(0),
  walker_route_visible(false),
  stage_traceable_visible(false) {
}

MallTweakerContext::~MallTweakerContext() {
}

MallTweakerContext tweaker_ctx;
