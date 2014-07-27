/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "MallGame.h"

#include <GL/glew.h>

#include "util/logging/Logger.h"
#include "util/macro_util.h"

MallGame::MallGame() : initialized_(false), quadric_(nullptr) {
}

MallGame::~MallGame() {
  if (initialized_) {
    if (!Logger::is_destroyed()) {
      LOGGER.Warn("Need to finalize the game");
    }
  }
}

int MallGame::Initialize(int window_width, int window_height) {
  LOGGER.Info("Set up the game");

  // setup viewport
  glViewport(0, 0, window_width, window_height);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glEnable(GL_DEPTH_TEST);

  // setup projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glLoadMatrixf(
      glm::value_ptr(
          glm::perspective(
              45.0f,
              static_cast<GLfloat>(window_width)
                  / static_cast<GLfloat>(window_height),
              1.0f, 200.0f)));

  // setup light
  static GLfloat position[] = { -10.0f, 10.0f, 10.0f, 1.0f };
  static GLfloat ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  static GLfloat diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  static GLfloat specular[] = { 0.0f, 0.0f, 0.0f, 0.0f };
  glLightfv(GL_LIGHT0, GL_POSITION, position);
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
  glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  quadric_ = gluNewQuadric();
  if (quadric_ == nullptr) {
    LOGGER.Error("Failed to create the quadric");
    return -1;
  }

  initialized_ = true;

  return 0;
}

void MallGame::Finalize() {
  if (!initialized_) {
    LOGGER.Notice("Ignored the duplicate call to finalize game");
    return;
  }

  LOGGER.Info("Clean up the game");

  if (quadric_ != nullptr) {
    gluDeleteQuadric(quadric_);
  }
  initialized_ = false;

  return;
}

void MallGame::Update(float elapsed_time) {
  UNUSED(elapsed_time);

  if (!initialized_) {
    return;
  }
  return;
}

int MallGame::Draw() {
  if (!initialized_) {
    return 1;
  }

  // clear
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // setup view
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glLoadMatrixf(
      glm::value_ptr(
          glm::lookAt(glm::vec3(0.0f, 0.0f, -30.0f), glm::vec3(),
                      glm::vec3(0.0f, -1.0f, 0.0f))));

  // setup material
  GLfloat ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
  GLfloat diffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f };
  GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  GLfloat shininess[] = { 0.0f };
  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

  gluSphere(quadric_, 10.0, 30, 30);

  return 0;
}
