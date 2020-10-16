#include "SlideWindow.h"
#include <iostream>

int SlideWindow::orderMapping(int seqNum) {
  int result = seqNum - base;
  if (result >= 0 && result <= 3)
    return result;
  else if (result > 3)
    return result - 8;
  else if (result < -4)
    return result + seqLength;
  else if (result < 0 && result >= -4)
    return result;
}

void SlideWindow::setSeqLength(int len) { seqLength = len; }

void SlideWindow::setWinSize(int size) { winSize = size; }