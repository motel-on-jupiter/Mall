/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "MouseCageScene.h"
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

MouseCageScene::MouseCageScene() {
}

MouseCageScene::~MouseCageScene() {
}

int MouseCageScene::Initialize(const glm::vec2& stage_size) {
  return stage.Initialize(stage_size);
}

void MouseCageScene::Finalize() {
  stage.Finalize();
}

int MouseCageScene::Update(float elapsed_time) {
  UNUSED(elapsed_time);

  return 0;
}

int MouseCageScene::Draw() {
  stage.Draw();
  return 0;
}

int MouseCageScene::OnMouseButtonDown(unsigned char button,
                                  const glm::vec2& cursor_pos) {
  UNUSED(button);
  UNUSED(cursor_pos);

  return 0;
}
