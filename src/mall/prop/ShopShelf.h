/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#ifndef SHOPSHELF_H_
#define SHOPSHELF_H_

#include "entity/BaseEntity.h"
#include "entity/EntityDraw.h"

class Waypoint;

class ShopShelf : public BaseEntity, public EntityRectangleDraw {
 public:
  ShopShelf(const glm::vec2 &pos, float rot, const glm::vec2 &scale,
            std::string stockitem, unsigned int stocknum,
            const Waypoint &waypoint);
  virtual ~ShopShelf() {}

  const std::string& stockitem() const { return stockitem_; }
  unsigned int stocknum() const { return stocknum_; }
  void set_stocknum(unsigned int stocknum) { stocknum_ = stocknum; }
  const Waypoint &waypoint() const { return waypoint_; }

 private:
  std::string stockitem_;
  unsigned int stocknum_;
  const Waypoint &waypoint_;
};

#endif /* SHOPSHELF_H_ */
