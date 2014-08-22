/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "MallGame.h"

#include <GL/glew.h>
#include <SDL_surface.h>
#include <SDL_ttf.h>
#include <SDL_video.h>

#include "mall/scene/BridgeScene.h"
#include "mall/scene/ConvenienceStoreScene.h"
#include "mall/scene/GridScene.h"
#include "mall/scene/MouseCageScene.h"
#include "util/logging/Logger.h"
#include "util/macro_util.h"

MallGame::MallGame() : scene_(nullptr), font_(nullptr) {
}

MallGame::~MallGame() {
  Finalize();
}

int MallGame::Initialize(const glm::vec2 &stage_size) {
  // Set the parameter
  stagesize_ = stage_size;

  // Load font
  font_ = TTF_OpenFont("share/ipag00303/ipag.ttf", 24);
  if (font_ == nullptr) {
    LOGGER.Error("Failed to open font with SDL_ttf (errmsg: %s)",
                 TTF_GetError());
    return -1;
  }
  return 0;
}

void MallGame::Finalize() {
  if (scene_ != nullptr) {
    scene_->Finalize();
    delete scene_;
    scene_ = nullptr;
  }
  if (font_ != nullptr) {
    TTF_CloseFont(font_);
    font_ = nullptr;
  }
}

int MallGame::Update(float elapsed_time) {
  if (scene_ == nullptr) {
    return 2;
  }
  return scene_->Update(elapsed_time);
}

int MallGame::Draw(const glm::vec2 &window_size) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (scene_ == nullptr) {
    return 0;
  }

  // Load the orthographic projection matrix
  glPushMatrix();
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, static_cast<GLdouble>(window_size.x),
          static_cast<GLdouble>(window_size.y), 0.0, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadMatrixf(glm::value_ptr(glm::scale(glm::vec3(40.0f, 40.0f, 1.0f))));
  int ret = scene_->Draw();
  glPopMatrix();

  return ret;
}

int MallGame::OnKeyboardDown(SDL_Keycode key) {
  if (scene_ == nullptr) {
    if ((key >= SDLK_1) && (key <= SDLK_4)) {
      if (key == SDLK_1) {
        LOGGER.Info("Set up GridScene");
        scene_ = new GridScene();
      } else if (key == SDLK_2) {
        LOGGER.Info("Set up BridgeScene");
        scene_ = new BridgeScene();
      } else if (key == SDLK_3) {
        LOGGER.Info("Set up ConvenienceStoreScene");
        scene_ = new ConvenienceStoreScene();
      } else {
        LOGGER.Info("Set up MouseCageScene");
        scene_ = new MouseCageScene();
      }
      int ret = scene_->Initialize(stagesize_);
      if (ret < 0) {
        LOGGER.Error("Failed to initialize the game case");
        return -1;
      }
    }
  } else {
    if (key == SDLK_0) {
      LOGGER.Info("Clean up the game-case");
      scene_->Finalize();
      delete scene_;
      scene_ = nullptr;
    }
  }
  return 0;
}

int MallGame::OnMouseButtonDown(unsigned char button, int x, int y, const glm::vec2 &window_size) {
  if (scene_ != nullptr) {
    auto abs_cursor_pos = glm::vec2(static_cast<float>(x), static_cast<float>(y));
    return scene_->OnMouseButtonDown(button, abs_cursor_pos / window_size);
  }
  return 0;
}
