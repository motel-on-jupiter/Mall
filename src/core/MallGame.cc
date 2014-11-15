/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "MallGame.h"

#include "core/scene/BridgeScene.h"
#include "core/scene/ConvenienceStoreScene.h"
#include "core/scene/GridScene.h"
#include "core/scene/MouseCageScene.h"
#include "mojgame/auxiliary/csyntax_aux.h"
#include "mojgame/includer/gl_include.h"
#include "mojgame/includer/sdl_include.h"
#include "mojgame/logging/Logger.h"

MallGame::MallGame()
: scenes_(), current_scene_(nullptr), stage_size_(), cursor_(0), ongoing_(false) {
}

MallGame::~MallGame() {
  Finalize();
}

int MallGame::Initialize(const glm::vec2 &stage_size) {
  MallBaseGameScene *scene = new GridScene();
  if (scene == nullptr) {
    mojgame::LOGGER().Error("Failed to create the grid scene");
    return -1;
  }
  scenes_.push_back(scene);
  scene = new BridgeScene();
  if (scene == nullptr) {
    mojgame::LOGGER().Error("Failed to create the bridge scene");
    return -1;
  }
  scenes_.push_back(scene);
  scene = new ConvenienceStoreScene();
  if (scene == nullptr) {
    mojgame::LOGGER().Error("Failed to create the covenience store scene");
    return -1;
  }
  scenes_.push_back(scene);
  scene = new MouseCageScene();
  if (scene == nullptr) {
    mojgame::LOGGER().Error("Failed to create the mouse cage scene");
    return -1;
  }
  scenes_.push_back(scene);

  stage_size_ = stage_size;
  ongoing_ = true;
  return 0;
}

void MallGame::Finalize() {
  if (current_scene_) {
    current_scene_->Finalize();
    current_scene_ = nullptr;
  }
  for (auto it = scenes_.begin(); it != scenes_.end(); ++it) {
    delete *it;
  }
  scenes_.clear();
}

int MallGame::Update(float elapsed_time) {
  if (!ongoing_) {
    return 0;
  }
  if (current_scene_ == nullptr) {
    return 2;
  }
  return current_scene_->Update(elapsed_time);
}

int MallGame::Draw(const glm::vec2 &window_size) {
  if (!ongoing_) {
    return 0;
  }

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (current_scene_ == nullptr) {
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(
        glm::value_ptr(glm::ortho(0.0f, window_size.x, window_size.y, 0.0f)));

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec2 name_pos = glm::vec2(10.0f, 20.0f);
    unsigned int idx = 0;
    for (auto it = scenes_.begin(); it != scenes_.end(); ++it) {
      glRasterPos2fv(glm::value_ptr(name_pos));
      glutBitmapString(
          GLUT_BITMAP_9_BY_15,
          reinterpret_cast<const unsigned char *>((
              (idx == cursor_) ? "-> " : "   ")));
      glutBitmapString(
          GLUT_BITMAP_9_BY_15,
          reinterpret_cast<const unsigned char *>((*it)->name().c_str()));
      name_pos += glm::vec2(0.0f, 12);
      ++idx;
    }
    return 0;
  } else {
    // Load the orthographic projection matrix
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, static_cast<GLdouble>(window_size.x),
            static_cast<GLdouble>(window_size.y), 0.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(glm::scale(glm::vec3(40.0f, 40.0f, 1.0f))));
    int ret = current_scene_->Draw();
    glPopMatrix();
    return ret;
  }
}

int MallGame::OnKeyboardDown(SDL_Keycode key) {
  if (!ongoing_) {
    return 0;
  }

  if (current_scene_ == nullptr) {
    switch (key) {
      case SDLK_j:
      case SDLK_DOWN:
        if (cursor_ < scenes_.size() -1) {
          ++cursor_;
        }
        break;
      case SDLK_k:
      case SDLK_UP:
        if (cursor_ > 0) {
          --cursor_;
        }
        break;
      case SDLK_RETURN: {
        MallBaseGameScene *setup_scene = scenes_.at(cursor_);
        mojgame::LOGGER().Info("Set up the game scene (scene: %s)",
                    setup_scene->name().c_str());
        int ret = setup_scene->Initialize(stage_size_);
        if (ret < 0) {
          mojgame::LOGGER().Error("Failed to setup the scene (ret: %d, scene: %s)", ret,
                       setup_scene->name().c_str());
          return -1;
        }
        current_scene_ = setup_scene;
        break;
      }
      case SDLK_ESCAPE:
        ongoing_ = false;
        break;
    }
  } else {
    if (key == SDLK_ESCAPE) {
      mojgame::LOGGER().Info("Clean up the game scene");
      current_scene_->Finalize();
      current_scene_ = nullptr;
    }
  }
  return 0;
}

int MallGame::OnMouseButtonDown(unsigned char button, int x, int y, const glm::vec2 &window_size) {
  if (!ongoing_) {
    return 0;
  }

  if (current_scene_ != nullptr) {
    auto abs_cursor_pos = glm::vec2(static_cast<float>(x), static_cast<float>(y));
    return current_scene_->OnMouseButtonDown(button, abs_cursor_pos / window_size);
  }
  return 0;
}
