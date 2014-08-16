/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "FPSCounter.h"

FPSCounter::FPSCounter(int sampling_msec)
: sampling_msec_(sampling_msec),
  fps_(0),
  count_(0),
  count_start_msec(0) {
}

void FPSCounter::Update(int current_msec) {
  // Count frames
  ++count_;

  // Update FPS
  int elapsed_msec = current_msec - count_start_msec;
  if (elapsed_msec > sampling_msec_) {
    fps_ = (sampling_msec_ * count_ / elapsed_msec) / (sampling_msec_ / 1000);
    count_ = 0;
    count_start_msec = current_msec;
  }
}
