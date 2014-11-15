/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "core/prop/ShopShelf.h"
#include "navigation/Waypoint.h"
#include "util/color_sample.h"

ShopShelf::ShopShelf(const glm::vec2 &pos, float rot, const glm::vec2 &scale,
                     std::string stockitem, unsigned int stocknum,
                     const Waypoint &waypoint)
: BaseEntity(pos, rot, scale),
  EntityRectangleDraw(*this, false, WebColor::kGray),
  stockitem_(stockitem),
  stocknum_(stocknum),
  waypoint_(waypoint) {
}
