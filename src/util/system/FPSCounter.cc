/**
 * Copyright (C) 2014 The Motel On Jupiter
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "FPSCounter.h"

FPSCounter::FPSCounter(int intervaltime)
    : intervaltime_(intervaltime),
      count_(0),
      countstarttime_(0),
      fps_(0) {
}

FPSCounter::~FPSCounter() {
}

int FPSCounter::Update(int nowtime) {
  // update_interval_��0�ȉ��̎��͍X�V���Ȃ�
  if (0 >= intervaltime_) {
    return 1;
  }

  // �t���[�������J�E���g
  ++count_;

  //
  int elapsedtime = nowtime - countstarttime_;
  if (elapsedtime > intervaltime_) {
    //�v��
    fps_ = (intervaltime_ * count_ / elapsedtime) / (intervaltime_ / 1000);

    //������
    countstarttime_ = nowtime;
    count_ = 0;
  }

  return 0;
}

