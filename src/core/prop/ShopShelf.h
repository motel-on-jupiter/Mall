/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#ifndef CORE_PROP_SHOPSHELF_H_
#define CORE_PROP_SHOPSHELF_H_

#include "mojgame/catalogue/entity_extention/PlanarEntityDraw.h"
#include "mojgame/entity/PlanarEntity.h"
#include "mojgame/navigation/Waypoint.h"

class ShopShelf : public mojgame::PlanarEntity,
    public mojgame::EntityRectangleDraw,
    public mojgame::NonCopyable<ShopShelf> {
 public:
  ShopShelf(const glm::vec2 &pos, float rot, const glm::vec2 &scale,
            std::string stockitem, unsigned int stocknum,
            const mojgame::Waypoint &waypoint);
  virtual ~ShopShelf() {
  }

  const std::string& stockitem() const {
    return stockitem_;
  }
  unsigned int stocknum() const {
    return stocknum_;
  }
  void set_stocknum(unsigned int stocknum) {
    stocknum_ = stocknum;
  }
  const mojgame::Waypoint &waypoint() const {
    return waypoint_;
  }

 private:
  std::string stockitem_;
  unsigned int stocknum_;
  const mojgame::Waypoint &waypoint_;
};

#endif /* CORE_PROP_SHOPSHELF_H_ */
