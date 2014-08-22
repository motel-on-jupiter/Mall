/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "MouseCageScene.h"
#include "mall/actor/Mouse.h"
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

MouseCageScene::MouseCageScene() : stage_(), mouse_(nullptr) {
}

MouseCageScene::~MouseCageScene() {
}

int MouseCageScene::Initialize(const glm::vec2& stage_size) {
  int ret = stage_.Initialize(stage_size);
  if (ret < 0) {
    LOGGER.Error("Failed to initialize the stage (ret: %d)", ret);
    return -1;
  }
  mouse_ = new Mouse(glm::vec2(0.0f), 0.0f, glm::vec2(1.0f));
  if (mouse_ == nullptr) {
    LOGGER.Error("Failed to create the mouse object");
    return -1;
  }
  return 0;
}

void MouseCageScene::Finalize() {
  delete mouse_;
  mouse_ = nullptr;
  stage_.Finalize();
}

int MouseCageScene::Update(float elapsed_time) {
  UNUSED(elapsed_time);

  return 0;
}

int MouseCageScene::Draw() {
  stage_.Draw();
  if (mouse_ != nullptr) {
    mouse_->Draw();
  }
  return 0;
}

int MouseCageScene::OnMouseButtonDown(unsigned char button,
                                  const glm::vec2& cursor_pos) {
  UNUSED(button);
  UNUSED(cursor_pos);

  return 0;
}
