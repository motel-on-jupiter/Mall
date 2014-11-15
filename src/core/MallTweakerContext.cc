/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "core/MallTweakerContext.h"

MallTweakerContext::MallTweakerContext()
: system_actual_fps(0),
  system_time_speed(1.0f),
  walker_route_visible(false),
  stage_waypoint_visible(false),
  stage_traceable_visible(false) {
}

MallTweakerContext::~MallTweakerContext() {
}

MallTweakerContext tweaker_ctx;
