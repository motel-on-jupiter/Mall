/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "MallGame.h"
#include <GL/glew.h>
#include "mall/case/BridgeTrafficCase.h"
#include "mall/case/GridWalkingCase.h"
#include "util/logging/Logger.h"
#include "util/macro_util.h"

MallGame::MallGame() :
  gamecase_(nullptr) {
}

MallGame::~MallGame() {
  Finalize();
}

void MallGame::Initialize() {
}

void MallGame::Finalize() {
  if (gamecase_ == nullptr) {
    return;
  }
  gamecase_->Finalize();
  delete gamecase_;
  gamecase_ = nullptr;
}

void MallGame::Update(float elapsed_time) {
  if (gamecase_ == nullptr) {
    return;
  }
  gamecase_->Update(elapsed_time);
}

int MallGame::Draw(glm::vec2 window_size) {
  if (gamecase_ == nullptr) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    return 0;
  }
  return gamecase_->Draw(window_size);
}

int MallGame::OnKeyboardDown(SDL_Keycode key, glm::vec2 window_size) {
  if (gamecase_ == nullptr) {
    if ((key == SDLK_1) || (key == SDLK_2)) {
      if (key == SDLK_1) {
        LOGGER.Info("Set up GridWalkingCase");
        gamecase_ = new GridWalkingCase();
      } else {
        LOGGER.Info("Set up BridgeTrafficCase");
        gamecase_ = new BridgeTrafficCase();
      }
      int ret = gamecase_->Initialize(window_size);
      if (ret < 0) {
        LOGGER.Error("Failed to initialize the game case");
        return -1;
      }
    }
  } else {
    if (key == SDLK_0) {
      LOGGER.Info("Clean up the game-case");
      gamecase_->Finalize();
      delete gamecase_;
      gamecase_ = nullptr;
    }
  }
  return 0;
}

int MallGame::OnMouseButtonDown(unsigned char button, int x, int y, glm::vec2 window_size) {
  if (gamecase_ != nullptr) {
    return gamecase_->OnMouseButtonDown(button, x, y, window_size);
  }
  return 0;
}
