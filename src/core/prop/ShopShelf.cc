/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "core/prop/ShopShelf.h"
#include "mojgame/navigation/Waypoint.h"
#include "mojgame/sampler/color_sample.h"

ShopShelf::ShopShelf(const glm::vec2 &pos, float rot, const glm::vec2 &scale,
                     std::string stockitem, unsigned int stocknum,
                     const mojgame::Waypoint &waypoint)
    : mojgame::PlanarEntity(pos, rot, scale),
      mojgame::EntityRectangleDraw(*this, false, mojgame::WebColor::kGray),
      stockitem_(stockitem),
      stocknum_(stocknum),
      waypoint_(waypoint) {
}
