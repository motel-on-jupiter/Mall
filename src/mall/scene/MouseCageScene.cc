/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "MouseCageScene.h"
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

MouseCageScene::MouseCageScene() : stage_(), mouse_(nullptr), food_(nullptr) {
}

MouseCageScene::~MouseCageScene() {
}

int MouseCageScene::Initialize(const glm::vec2& stage_size) {
  int ret = stage_.Initialize(stage_size);
  if (ret < 0) {
    LOGGER.Error("Failed to initialize the stage (ret: %d)", ret);
    return -1;
  }
  mouse_ = new Mouse(stage_size * 0.5f, 0.0f, glm::vec2(1.0f));
  if (mouse_ == nullptr) {
    LOGGER.Error("Failed to create the mouse object");
    return -1;
  }
  food_ = new MouseFood(stage_size * glm::vec2(0.25f, 0.5f), 0.0f, glm::vec2(1.0f));
  if (food_ == nullptr) {
    LOGGER.Error("Failed to create the mouse-food object");
    return -1;
  }
  return 0;
}

void MouseCageScene::Finalize() {
  delete food_;
  food_ = nullptr;
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
  if (mouse_ != nullptr) {
    mouse_->Draw();
  }
  if (food_ != nullptr) {
    food_->Draw();
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
