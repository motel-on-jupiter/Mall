/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "MouseCageScene.h"
#include <boost/foreach.hpp>
#include "mall/actor/Mouse.h"
#include "mall/prop/MouseFood.h"
#include "util/logging/Logger.h"
#include "util/macro_util.h"

MouseCageStage::MouseCageStage() {
}

MouseCageStage::~MouseCageStage() {
}

int MouseCageStage::Initialize(const glm::vec2& size) {
  UNUSED(size);

  return 0;
}

void MouseCageStage::Finalize() {
}

MouseCageScene::MouseCageScene()
: MallBaseGameScene("Mouse Cage"), stage_(), cheeses_(), waters_(), mouse_(nullptr) {
}

MouseCageScene::~MouseCageScene() {
}

int MouseCageScene::Initialize(const glm::vec2& stage_size) {
  int ret = stage_.Initialize(stage_size);
  if (ret < 0) {
    LOGGER.Error("Failed to initialize the stage (ret: %d)", ret);
    return -1;
  }

  MouseCheese *cheese = new MouseCheese(stage_size * glm::vec2(0.25f, 0.5f), 0.0f, glm::vec2(1.0f));
  if (cheese == nullptr) {
    LOGGER.Error("Failed to create the cheese object");
    return -1;
  }
  cheeses_.push_back(cheese);

  MouseWater *water = new MouseWater(stage_size * glm::vec2(0.75f, 0.5f), 0.0f, glm::vec2(1.0f));
  if (water == nullptr) {
    LOGGER.Error("Failed to create the water object");
    return -1;
  }
  waters_.push_back(water);

  mouse_ = new Mouse(stage_size * 0.5f, 0.0f, glm::vec2(1.0f), cheeses_, waters_);
  if (mouse_ == nullptr) {
    LOGGER.Error("Failed to create the mouse object");
    return -1;
  }

  return 0;
}

void MouseCageScene::Finalize() {
  BOOST_FOREACH(auto water, waters_) {
    delete water;
  }
  waters_.clear();
  BOOST_FOREACH(auto cheese, cheeses_) {
    delete cheese;
  }
  cheeses_.clear();
  delete mouse_;
  mouse_ = nullptr;
  stage_.Finalize();
}

int MouseCageScene::Update(float elapsed_time) {
  UNUSED(elapsed_time);

  if (mouse_ != nullptr) {
    mouse_->Update(elapsed_time);
  }
  return 0;
}

int MouseCageScene::Draw() {
  stage_.Draw();
  BOOST_FOREACH(auto cheese, cheeses_) {
    cheese->Draw();
  }
  BOOST_FOREACH(auto water, waters_) {
    water->Draw();
  }
  if (mouse_ != nullptr) {
    mouse_->Draw();
  }
  return 0;
}

int MouseCageScene::OnMouseButtonDown(unsigned char button,
                                      const glm::vec2& cursor_pos) {
  UNUSED(cursor_pos);

  if (button == 1) {
    LOGGER.Info("appetite(food): %f, appetite(drink): %f, sleep: %f",
                mouse_->GetAppetiteForFood(),
                mouse_->GetAppetiteForDrink(),
                mouse_->GetDesireForSleep());
  }
  return 0;
}
