/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "mall/prop/ShopShelf.h"
#include "util/color_sample.h"

ShopShelf::ShopShelf(const glm::vec2 &pos, float rot, const glm::vec2 &scale,
                     std::string item, unsigned int itemstock)
: BaseEntity(pos, rot, scale),
  EntityRectangleDraw(*this, false, WebColor::kGray),
  item_(item), itemstock_(itemstock) {
}
