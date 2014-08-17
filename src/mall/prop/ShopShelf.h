/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#ifndef SHOPSHELF_H_
#define SHOPSHELF_H_

#include "entity/BaseEntity.h"
#include "entity/EntityDraw.h"

class ShopShelf : public BaseEntity, public EntityRectangleDraw {
 public:
  ShopShelf(const glm::vec2 &pos, float rot, const glm::vec2 &scale,
            std::string item, unsigned int itemstock);
  virtual ~ShopShelf() {}

  const std::string& item() const { return item_; }
  unsigned int itemstock() const { return itemstock_; }
  void set_itemstock(unsigned int itemstock) { itemstock_ = itemstock; }

 private:
  std::string item_;
  unsigned int itemstock_;
};

#endif /* SHOPSHELF_H_ */
