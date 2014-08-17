/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "mall/MallTweakContext.h"

MallTweakContext::MallTweakContext()
: ideal_fps(0),
  actual_fps(0),
  walker_route_visible(true) {
}

MallTweakContext::~MallTweakContext() {
}

MallTweakContext tweak_ctx;
