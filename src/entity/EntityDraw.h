/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#ifndef ENTITYDRAW_H_
#define ENTITYDRAW_H_

#include "entity/BaseEntity.h"

class EntityDraw : public EntityMixIn {
 public:
  EntityDraw(BaseEntity &entity) : EntityMixIn(entity) {}
  virtual ~EntityDraw() {}

  virtual void Draw() = 0;
};

class EntityPointDraw : public EntityDraw {
 public:
  EntityPointDraw(BaseEntity &entity);
  virtual ~EntityPointDraw() {}

  virtual void Draw();
};

class EntityTriangleDraw : public EntityDraw {
 public:
  EntityTriangleDraw(BaseEntity &entity, bool fill);
  virtual ~EntityTriangleDraw() {}

  virtual void Draw();

  bool fill() const { return fill_; }
  void set_fill(bool fill) { fill_ = fill; }

 private:
  bool fill_;
};

class EntityRectangleDraw : public EntityDraw {
 public:
  EntityRectangleDraw(BaseEntity &entity, bool fill);
  virtual ~EntityRectangleDraw() {}

  virtual void Draw();

  bool fill() const { return fill_; }
  void set_fill(bool fill) { fill_ = fill; }

 private:
  bool fill_;
};

#endif /* ENTITYDRAW_H_ */
