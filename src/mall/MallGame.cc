/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "MallGame.h"

#include <GL/glew.h>
#include <SDL_surface.h>
#include <SDL_video.h>

#include "mall/scene/BridgeScene.h"
#include "mall/scene/ConvenienceStoreScene.h"
#include "mall/scene/GridScene.h"
#include "mall/scene/MouseCageScene.h"
#include "util/logging/Logger.h"
#include "util/macro_util.h"

MallGame::MallGame()
: scenes_(), activescene_(nullptr), stagesize_() {
}

MallGame::~MallGame() {
  Finalize();
}

int MallGame::Initialize(const glm::vec2 &stage_size) {
  MallGameSceneInterface *scene = new GridScene();
  if (scene == nullptr) {
    LOGGER.Error("Failed to create the grid scene");
    return -1;
  }
  scenes_.push_back(scene);
  scene = new BridgeScene();
  if (scene == nullptr) {
    LOGGER.Error("Failed to create the bridge scene");
    return -1;
  }
  scenes_.push_back(scene);
  scene = new ConvenienceStoreScene();
  if (scene == nullptr) {
    LOGGER.Error("Failed to create the covenience store scene");
    return -1;
  }
  scenes_.push_back(scene);
  scene = new MouseCageScene();
  if (scene == nullptr) {
    LOGGER.Error("Failed to create the mouse cage scene");
    return -1;
  }
  scenes_.push_back(scene);

  // Set the parameter
  stagesize_ = stage_size;

  return 0;
}

void MallGame::Finalize() {
  if (activescene_) {
    activescene_->Finalize();
    activescene_ = nullptr;
  }
  BOOST_FOREACH(MallGameSceneInterface *scene, scenes_) {
    delete scene;
  }
  scenes_.clear();
}

int MallGame::Update(float elapsed_time) {
  if (activescene_ == nullptr) {
    return 2;
  }
  return activescene_->Update(elapsed_time);
}

int MallGame::Draw(const glm::vec2 &window_size) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (activescene_ == nullptr) {
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
  int ret = activescene_->Draw();
  glPopMatrix();

  return ret;
}

int MallGame::OnKeyboardDown(SDL_Keycode key) {
  if (activescene_ == nullptr) {
    if ((key >= SDLK_1) && (key <= SDLK_9)) {
      if (key - SDLK_1 < static_cast<int>(scenes_.size())) {
        LOGGER.Info("Set up the game scene");
        activescene_ = scenes_.at(key - SDLK_1);
        int ret = activescene_->Initialize(stagesize_);
        if (ret < 0) {
          LOGGER.Error("Failed to initialize the game case");
          return -1;
        }
      }
    }
  } else {
    if (key == SDLK_0) {
      LOGGER.Info("Clean up the game scene");
      activescene_->Finalize();
      activescene_ = nullptr;
    }
  }
  return 0;
}

int MallGame::OnMouseButtonDown(unsigned char button, int x, int y, const glm::vec2 &window_size) {
  if (activescene_ != nullptr) {
    auto abs_cursor_pos = glm::vec2(static_cast<float>(x), static_cast<float>(y));
    return activescene_->OnMouseButtonDown(button, abs_cursor_pos / window_size);
  }
  return 0;
}
